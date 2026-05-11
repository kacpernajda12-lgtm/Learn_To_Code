// 03 - Operators

// =========================================================
// ARITHMETIC
// =========================================================

console.log(10 + 3);   // 13
console.log(10 - 3);   // 7
console.log(10 * 3);   // 30
console.log(10 / 3);   // 3.333...  (always float division)
console.log(10 % 3);   // 1         (remainder)
console.log(2 ** 8);   // 256       (exponentiation)

let x = 5;
x++;           // post-increment: use then increment
console.log(x); // 6
++x;           // pre-increment: increment then use
console.log(x); // 7

// Math object for common operations
console.log(Math.abs(-9));      // 9
console.log(Math.floor(3.9));   // 3
console.log(Math.ceil(3.1));    // 4
console.log(Math.round(3.5));   // 4
console.log(Math.max(1, 5, 3)); // 5
console.log(Math.sqrt(16));     // 4


// =========================================================
// COMPARISON — == vs ===
// =========================================================

// === (strict equality) — checks value AND type; always use this
console.log(5 === 5);     // true
console.log(5 === "5");   // false — different types
console.log(null === undefined); // false

// == (loose equality) — coerces types; leads to surprises
console.log(5 == "5");    // true  — "5" is coerced to 5
console.log(0 == false);  // true  — false coerced to 0
console.log(null == undefined); // true — special case
console.log(null == 0);   // false — null only equals undefined loosely

console.log(3 > 2);   // true
console.log(3 >= 3);  // true
console.log("b" > "a"); // true — strings compared lexicographically


// =========================================================
// LOGICAL OPERATORS
// =========================================================

// && returns the first falsy value, or the last value if all truthy
console.log(true && "hello");   // "hello"
console.log(false && "hello");  // false
console.log(0 && "hello");      // 0      (0 is falsy)

// || returns the first truthy value, or the last value if all falsy
console.log(false || "default"); // "default"
console.log("alice" || "bob");   // "alice"
console.log(0 || null || "ok");  // "ok"

// ?? (nullish coalescing) — returns right side only if left is null/undefined
// Unlike ||, it does NOT treat 0 or "" as fallback triggers
console.log(null ?? "fallback");      // "fallback"
console.log(undefined ?? "fallback"); // "fallback"
console.log(0 ?? "fallback");         // 0   ← different from ||
console.log("" ?? "fallback");        // ""  ← different from ||

// ! negation
console.log(!true);   // false
console.log(!0);      // true  (0 is falsy)
console.log(!!"str"); // true  (double-negation converts to boolean)


// =========================================================
// ASSIGNMENT SHORTCUTS
// =========================================================

let n = 10;
n += 5;   // n = n + 5  → 15
n -= 3;   // n = n - 3  → 12
n *= 2;   // n = n * 2  → 24
n /= 4;   // n = n / 4  → 6
n **= 2;  // n = n ** 2 → 36
n ??= 0;  // assign only if n is null/undefined — it's 36, so no change
console.log(n); // 36


// =========================================================
// TERNARY & OPTIONAL CHAINING
// =========================================================

const age = 20;
const status = age >= 18 ? "adult" : "minor";
console.log(status); // "adult"

// ?. (optional chaining) — short-circuits to undefined instead of throwing
const user = { address: { city: "Warsaw" } };
console.log(user?.address?.city);    // "Warsaw"
console.log(user?.phone?.number);    // undefined  (no error thrown)
