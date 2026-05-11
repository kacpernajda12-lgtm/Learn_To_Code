// 09 - Closures and Scope

// =========================================================
// SCOPE — where a variable is visible
// =========================================================

const globalVar = "I am global";       // visible everywhere in this file

function outer() {
    const outerVar = "I am outer";     // visible inside outer() and its children

    function inner() {
        const innerVar = "I am inner"; // visible only inside inner()
        console.log(globalVar);        // ✓ can reach global scope
        console.log(outerVar);         // ✓ can reach enclosing scope
        console.log(innerVar);         // ✓ own scope
    }

    inner();
    // console.log(innerVar);          // ✗ would throw ReferenceError
}

outer();

// Block scope — let and const are confined to the nearest { }
{
    const blockVar = "only in this block";
    let blockLet   = "same";
    console.log(blockVar); // ok
}
// console.log(blockVar); // ✗ ReferenceError


// =========================================================
// HOISTING — declarations are moved to the top of their scope at compile time
// =========================================================

// var is hoisted AND initialized to undefined
console.log(hoisted);     // undefined (no error)
var hoisted = "value";

// let/const are hoisted but NOT initialized — accessing before declaration throws
// console.log(notYet);  // ✗ ReferenceError: Cannot access 'notYet' before initialization
// let notYet = "value";

// Function declarations are fully hoisted (name + body)
console.log(hoistedFn()); // "I work before my declaration"
function hoistedFn() { return "I work before my declaration"; }

// Function expressions are NOT hoisted
// console.log(notHoisted()); // ✗ TypeError
// const notHoisted = () => "nope";


// =========================================================
// CLOSURES — a function that remembers variables from the scope where it was created
// =========================================================

function makeCounter(start = 0) {
    let count = start;        // this variable lives on after makeCounter returns

    return {
        increment() { count++; },
        decrement() { count--; },
        value()     { return count; },
        reset()     { count = start; },
    };
}

const counter = makeCounter(10);
counter.increment();
counter.increment();
counter.decrement();
console.log(counter.value()); // 11

// Each call creates an independent closure — they don't share state
const c1 = makeCounter();
const c2 = makeCounter(100);
c1.increment();
c2.increment();
console.log(c1.value(), c2.value()); // 1, 101


// =========================================================
// PRACTICAL CLOSURE PATTERNS
// =========================================================

// Memoization — cache previous results to avoid redundant work
function memoize(fn) {
    const cache = new Map();
    return function (...args) {
        const key = JSON.stringify(args);
        if (cache.has(key)) return cache.get(key);
        const result = fn(...args);
        cache.set(key, result);
        return result;
    };
}

const slowSquare = (n) => {
    // simulates expensive computation (no actual sleep here)
    return n * n;
};

const fastSquare = memoize(slowSquare);
console.log(fastSquare(7)); // computed: 49
console.log(fastSquare(7)); // from cache: 49

// Partial application — fix some arguments ahead of time
function partial(fn, ...presetArgs) {
    return (...laterArgs) => fn(...presetArgs, ...laterArgs);
}

const multiply = (a, b) => a * b;
const triple   = partial(multiply, 3);
console.log(triple(5));   // 15
console.log(triple(10));  // 30


// =========================================================
// IIFE — Immediately Invoked Function Expression
// =========================================================

// Used to create a private scope without polluting the outer scope
const result = (function () {
    const privateData = 42;       // hidden from outside
    return privateData * 2;
})();

console.log(result);              // 84
// console.log(privateData);      // ✗ ReferenceError
