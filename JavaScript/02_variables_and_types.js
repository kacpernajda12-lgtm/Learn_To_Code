// 02 - Variables and Types

// =========================================================
// DECLARING VARIABLES
// =========================================================

// const — cannot be reassigned; prefer this by default
const pi = 3.14159;

// let — block-scoped, can be reassigned
let score = 0;
score = 10;

// var — function-scoped, hoisted; avoid in modern code
var legacy = "old style";

console.log(pi, score, legacy);


// =========================================================
// PRIMITIVE TYPES
// =========================================================

const str     = "hello";          // string
const num     = 42;               // number (integers AND floats share one type)
const float   = 3.14;            // still a number
const bool    = true;            // boolean
const nothing = null;            // intentional absence of value
let   missing;                   // undefined — declared but never assigned
const bigNum  = 9007199254740993n; // bigint — for integers beyond Number.MAX_SAFE_INTEGER
const sym     = Symbol("id");    // symbol — always unique

console.log(typeof str);     // "string"
console.log(typeof num);     // "number"
console.log(typeof bool);    // "boolean"
console.log(typeof nothing); // "object"  ← historical bug in JS, null is NOT an object
console.log(typeof missing); // "undefined"
console.log(typeof bigNum);  // "bigint"
console.log(typeof sym);     // "symbol"


// =========================================================
// TYPE COERCION — JS silently converts types in many operations
// =========================================================

// + with a string converts the other operand to string
console.log("5" + 3);     // "53"  (concatenation, not addition)
console.log("5" - 3);     // 2     (subtraction forces numeric conversion)
console.log(true + 1);    // 2     (true → 1)
console.log(false + 1);   // 1     (false → 0)
console.log(null + 1);    // 1     (null → 0)
console.log(undefined + 1); // NaN (undefined → NaN)

// Explicit conversion to avoid surprises
console.log(Number("42"));   // 42
console.log(Number(""));     // 0
console.log(Number("abc"));  // NaN
console.log(String(42));     // "42"
console.log(Boolean(0));     // false
console.log(Boolean(""));    // false
console.log(Boolean(null));  // false
console.log(Boolean("hi"));  // true
console.log(Boolean(1));     // true


// =========================================================
// SPECIAL NUMBER VALUES
// =========================================================

console.log(1 / 0);          // Infinity
console.log(-1 / 0);         // -Infinity
console.log(0 / 0);          // NaN
console.log(NaN === NaN);    // false — NaN is not equal to itself
console.log(isNaN(NaN));     // true  — use isNaN() or Number.isNaN()
console.log(Number.isFinite(Infinity)); // false
