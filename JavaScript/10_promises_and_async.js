// 10 - Promises and Async/Await

// =========================================================
// THE PROBLEM WITH CALLBACKS — "callback hell"
// =========================================================

// Imagine reading a file, parsing it, then fetching a URL — each step depends
// on the previous. With callbacks this nests infinitely:
//
// readFile(path, (err, data) => {
//     if (err) handle(err);
//     parseJSON(data, (err, json) => {
//         if (err) handle(err);
//         fetchURL(json.url, (err, res) => { ... });
//     });
// });
//
// Promises and async/await solve this by making async code look sequential.


// =========================================================
// PROMISES — represent a value that may arrive in the future
// =========================================================

// Creating a promise
function delay(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms));
}

function fetchUser(id) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            if (id > 0) {
                resolve({ id, name: `User_${id}` }); // success
            } else {
                reject(new Error("Invalid user id")); // failure
            }
        }, 10); // 10ms simulated latency
    });
}

// .then / .catch / .finally chaining
fetchUser(1)
    .then((user) => {
        console.log("Got user:", user.name);
        return user.id * 10;          // return value becomes input to next .then
    })
    .then((transformed) => {
        console.log("Transformed:", transformed); // 10
    })
    .catch((err) => {
        console.error("Error:", err.message);     // only runs on rejection
    })
    .finally(() => {
        console.log("Done (always runs)");
    });

// Rejected promise
fetchUser(-1)
    .then((u) => console.log(u))
    .catch((err) => console.log("Caught:", err.message)); // "Caught: Invalid user id"


// =========================================================
// PROMISE COMBINATORS
// =========================================================

// Promise.all — wait for ALL to resolve; rejects immediately if any rejects
Promise.all([fetchUser(1), fetchUser(2), fetchUser(3)]).then((users) => {
    console.log("All users:", users.map((u) => u.name));
});

// Promise.allSettled — wait for ALL, regardless of success or failure
Promise.allSettled([fetchUser(1), fetchUser(-1), fetchUser(3)]).then((results) => {
    for (const r of results) {
        if (r.status === "fulfilled") console.log("OK:", r.value.name);
        else                          console.log("FAIL:", r.reason.message);
    }
});

// Promise.race — resolves/rejects as soon as the FIRST settles
Promise.race([delay(50), delay(10)]).then(() => console.log("race done"));

// Promise.any — resolves with FIRST success; rejects only if ALL fail
Promise.any([fetchUser(-1), fetchUser(5)]).then((u) => {
    console.log("any resolved with:", u.name); // User_5
});


// =========================================================
// ASYNC / AWAIT — syntactic sugar over Promises
// =========================================================

// async functions always return a Promise
async function loadUser(id) {
    const user = await fetchUser(id); // pause here until the Promise resolves
    return user;
}

// await can only be used inside an async function
async function main() {
    console.log("\n--- async/await ---");

    // Sequential — each awaits the previous
    const u1 = await fetchUser(1);
    const u2 = await fetchUser(2);
    console.log("Sequential:", u1.name, u2.name);

    // Parallel — kick off both, then await together
    const [u3, u4] = await Promise.all([fetchUser(3), fetchUser(4)]);
    console.log("Parallel:", u3.name, u4.name);

    // Error handling with try/catch
    try {
        const bad = await fetchUser(-99);
    } catch (err) {
        console.log("Caught in async fn:", err.message);
    }
}

main();
