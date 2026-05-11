// 05 - Functions

// =========================================================
// FUNCTION DECLARATION — hoisted, callable before definition
// =========================================================

console.log(add(2, 3)); // 5 — works because declarations are hoisted

function add(a, b) {
    return a + b;
}


// =========================================================
// FUNCTION EXPRESSION — not hoisted, stored in a variable
// =========================================================

const multiply = function (a, b) {
    return a * b;
};
console.log(multiply(4, 5)); // 20


// =========================================================
// ARROW FUNCTIONS — shorter syntax, no own 'this'
// =========================================================

const square = (n) => n * n;          // implicit return for one expression
const greet  = (name) => `Hi, ${name}!`;
const noop   = () => {};               // no params, no return value

console.log(square(6));     // 36
console.log(greet("Alice")); // "Hi, Alice!"

// Multi-line arrow function needs curly braces and explicit return
const clamp = (value, min, max) => {
    if (value < min) return min;
    if (value > max) return max;
    return value;
};
console.log(clamp(15, 0, 10)); // 10


// =========================================================
// DEFAULT PARAMETERS
// =========================================================

function createUser(name, role = "user", active = true) {
    return { name, role, active };  // shorthand: {name: name} → {name}
}

console.log(createUser("Bob"));              // {name:"Bob", role:"user", active:true}
console.log(createUser("Alice", "admin"));   // role overridden, active uses default


// =========================================================
// REST PARAMETERS — collect extra arguments into an array
// =========================================================

function sum(...numbers) {
    return numbers.reduce((acc, n) => acc + n, 0);
}

console.log(sum(1, 2, 3, 4, 5)); // 15

function log(level, ...messages) {
    console.log(`[${level}]`, messages.join(" "));
}
log("INFO", "Server", "started", "on", "port", "3000");


// =========================================================
// SPREAD OPERATOR — expand an array/object into individual elements
// =========================================================

const nums = [3, 1, 4, 1, 5, 9];
console.log(Math.max(...nums));        // 9  — spread into arguments
console.log([0, ...nums, 10]);         // [0, 3, 1, 4, 1, 5, 9, 10]

const a = [1, 2];
const b = [3, 4];
console.log([...a, ...b]);             // [1, 2, 3, 4]


// =========================================================
// HIGHER-ORDER FUNCTIONS — functions that take/return functions
// =========================================================

function repeat(fn, times) {
    for (let i = 0; i < times; i++) fn(i);
}
repeat((i) => console.log(`tick ${i}`), 3);

function makeMultiplier(factor) {
    return (n) => n * factor;  // returns a new function (closure)
}
const double = makeMultiplier(2);
const triple = makeMultiplier(3);
console.log(double(5)); // 10
console.log(triple(5)); // 15


// =========================================================
// RECURSION
// =========================================================

function factorial(n) {
    if (n <= 1) return 1;       // base case — stop recursion
    return n * factorial(n - 1); // recursive case
}
console.log(factorial(6)); // 720

function fibonacci(n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
console.log(fibonacci(10)); // 55
