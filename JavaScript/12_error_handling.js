// 12 - Error Handling

// =========================================================
// TRY / CATCH / FINALLY
// =========================================================

try {
    const obj = null;
    console.log(obj.name); // TypeError: cannot read properties of null
} catch (err) {
    console.log(`Caught: ${err.name} — ${err.message}`);
} finally {
    console.log("finally always runs (cleanup goes here)");
}

// Rethrowing — only handle errors you understand; let others bubble up
function parseJSON(text) {
    try {
        return JSON.parse(text);
    } catch (err) {
        if (err instanceof SyntaxError) {
            throw new SyntaxError(`Bad JSON input: ${err.message}`);
        }
        throw err; // unexpected error — rethrow unchanged
    }
}

try {
    parseJSON("{bad json}");
} catch (err) {
    console.log(err.message); // "Bad JSON input: ..."
}


// =========================================================
// BUILT-IN ERROR TYPES
// =========================================================

// Error         — generic base class
// TypeError     — wrong type (null.property, calling a non-function)
// RangeError    — value out of allowed range (new Array(-1))
// ReferenceError — unknown variable
// SyntaxError   — invalid code / JSON
// URIError      — malformed URI in decodeURI()

try { null.x;       } catch (e) { console.log(e.constructor.name); } // TypeError
try { new Array(-1);} catch (e) { console.log(e.constructor.name); } // RangeError


// =========================================================
// CUSTOM ERROR CLASSES
// =========================================================

class AppError extends Error {
    constructor(message, code) {
        super(message);
        this.name = "AppError";
        this.code = code;
    }
}

class NotFoundError extends AppError {
    constructor(resource, id) {
        super(`${resource} with id ${id} not found`, 404);
        this.name = "NotFoundError";
    }
}

class ValidationError extends AppError {
    constructor(field, reason) {
        super(`Validation failed on '${field}': ${reason}`, 422);
        this.name = "ValidationError";
        this.field = field;
    }
}

function findUser(id) {
    if (typeof id !== "number") throw new ValidationError("id", "must be a number");
    if (id <= 0)                throw new ValidationError("id", "must be positive");
    if (id > 100)               throw new NotFoundError("User", id);
    return { id, name: `User_${id}` };
}

for (const id of ["abc", -1, 999, 42]) {
    try {
        const user = findUser(id);
        console.log("Found:", user.name);
    } catch (err) {
        if (err instanceof ValidationError) {
            console.log(`[${err.code}] Validation: ${err.message}`);
        } else if (err instanceof NotFoundError) {
            console.log(`[${err.code}] Not found: ${err.message}`);
        } else {
            throw err; // unexpected — don't swallow it
        }
    }
}


// =========================================================
// ASYNC ERROR HANDLING
// =========================================================

async function riskyOperation(fail) {
    if (fail) throw new AppError("Something went wrong", 500);
    return "success";
}

// async errors must be caught with try/catch or .catch()
async function run() {
    // try/catch inside async function
    try {
        const result = await riskyOperation(false);
        console.log(result);          // "success"
        await riskyOperation(true);   // throws
    } catch (err) {
        console.log(`Async error: ${err.message}`);
    }

    // .catch() on a promise chain
    riskyOperation(true)
        .then((r) => console.log(r))
        .catch((err) => console.log("Chain caught:", err.message));
}

run();
