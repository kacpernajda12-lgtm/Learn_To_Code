// 14 - Functional Programming

// =========================================================
// CORE ARRAY METHODS — map, filter, reduce
// =========================================================

const products = [
    { name: "Laptop",  price: 1200, category: "electronics", inStock: true  },
    { name: "T-Shirt", price:   25, category: "clothing",    inStock: true  },
    { name: "Phone",   price:  800, category: "electronics", inStock: false },
    { name: "Jeans",   price:   60, category: "clothing",    inStock: true  },
    { name: "Tablet",  price:  500, category: "electronics", inStock: true  },
];

// map — transform each element, return same-length array
const names  = products.map((p) => p.name);
const prices = products.map((p) => p.price);
console.log(names);   // ["Laptop", "T-Shirt", ...]

// filter — keep elements that pass a test
const electronics = products.filter((p) => p.category === "electronics");
const available   = products.filter((p) => p.inStock);
console.log(electronics.length); // 3

// reduce — fold the array into a single value
const totalValue = products.reduce((acc, p) => acc + p.price, 0);
console.log(totalValue); // 2585

// Group items by category using reduce
const byCategory = products.reduce((acc, p) => {
    (acc[p.category] ??= []).push(p.name);  // ??= creates array if key is missing
    return acc;
}, {});
console.log(byCategory);
// { electronics: ["Laptop","Phone","Tablet"], clothing: ["T-Shirt","Jeans"] }


// =========================================================
// CHAINING — compose transformations in a readable pipeline
// =========================================================

const result = products
    .filter((p) => p.inStock)
    .filter((p) => p.category === "electronics")
    .map((p) => ({ name: p.name, price: p.price }))
    .sort((a, b) => a.price - b.price);

console.log(result);  // [{name:"Tablet",price:500}, {name:"Laptop",price:1200}]


// =========================================================
// OTHER USEFUL ARRAY METHODS
// =========================================================

const nums = [3, 1, 4, 1, 5, 9, 2, 6];

// find / findIndex — first match
console.log(nums.find((n) => n > 4));       // 5
console.log(nums.findIndex((n) => n > 4));  // 4

// some / every — boolean checks
console.log(nums.some((n) => n > 8));       // true  (9 exists)
console.log(nums.every((n) => n > 0));      // true  (all positive)

// flat / flatMap
const nested = [[1, 2], [3, 4], [5]];
console.log(nested.flat());                 // [1, 2, 3, 4, 5]

const sentences = ["hello world", "foo bar"];
console.log(sentences.flatMap((s) => s.split(" ")));
// ["hello", "world", "foo", "bar"]

// reduce to count occurrences
const freq = ["a", "b", "a", "c", "b", "a"].reduce((acc, ch) => {
    acc[ch] = (acc[ch] ?? 0) + 1;
    return acc;
}, {});
console.log(freq); // { a: 3, b: 2, c: 1 }


// =========================================================
// PURE FUNCTIONS — same input always gives same output, no side effects
// =========================================================

// Impure — depends on external state and mutates input
let total = 0;
function addToTotal(n) {        // impure: reads/writes external variable
    total += n;
    return total;
}

// Pure — self-contained, predictable
function add(a, b) {            // pure: only depends on its arguments
    return a + b;
}

// Pure functions are easier to test, compose, and reason about
const pureResult = [1, 2, 3].map(add.bind(null, 10));
console.log(pureResult); // [11, 12, 13]


// =========================================================
// IMMUTABILITY — create new data instead of mutating existing data
// =========================================================

const original = { name: "Alice", age: 30, role: "user" };

// Mutating (avoid)
// original.role = "admin"; // changes the object in place

// Immutable update — spread + override
const promoted = { ...original, role: "admin" };
console.log(original.role);  // "user"  — unchanged
console.log(promoted.role);  // "admin"

// Immutable array operations
const arr    = [1, 2, 3, 4, 5];
const noThree = arr.filter((n) => n !== 3);    // remove without splice
const doubled = arr.map((n) => n * 2);          // transform without mutation
const appended = [...arr, 6];                   // add without push
console.log(arr);        // [1, 2, 3, 4, 5]  — still intact
console.log(noThree);    // [1, 2, 4, 5]


// =========================================================
// FUNCTION COMPOSITION
// =========================================================

const compose = (...fns) => (x) => fns.reduceRight((acc, fn) => fn(acc), x);
const pipe    = (...fns) => (x) => fns.reduce((acc, fn) => fn(acc), x);

const trim      = (s) => s.trim();
const lower     = (s) => s.toLowerCase();
const capitalize= (s) => s[0].toUpperCase() + s.slice(1);

const normalize = pipe(trim, lower, capitalize);
console.log(normalize("  hELLO wORLD  ")); // "Hello world"
