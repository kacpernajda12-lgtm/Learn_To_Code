// 07 - Strings

// =========================================================
// BASICS
// =========================================================

// Single, double, and backtick (template literal) strings are equivalent
const s1 = 'hello';
const s2 = "world";
const s3 = `template`;

console.log(s1.length);          // 5
console.log("abc"[1]);           // "b"  — strings are index-accessible
console.log("abc".at(-1));       // "c"  — negative index

// Strings are immutable — methods always return a new string
const str = "  Hello, World!  ";


// =========================================================
// COMMON STRING METHODS
// =========================================================

console.log(str.trim());                   // "Hello, World!"  — strip whitespace
console.log(str.trimStart());              // strip leading only
console.log(str.trimEnd());               // strip trailing only

console.log("hello".toUpperCase());        // "HELLO"
console.log("HELLO".toLowerCase());        // "hello"

console.log("hello world".includes("world"));    // true
console.log("hello".startsWith("he"));           // true
console.log("hello".endsWith("lo"));             // true
console.log("hello world".indexOf("world"));     // 6
console.log("hello world".lastIndexOf("l"));     // 9

console.log("hello".slice(1, 3));          // "el"  — [start, end)
console.log("hello".slice(-3));            // "llo" — from end
console.log("hello".substring(1, 3));      // "el"  — no negative index support

console.log("ha".repeat(3));               // "hahaha"
console.log("5".padStart(4, "0"));         // "0005"
console.log("hi".padEnd(6, "."));          // "hi...."

console.log("a,b,c".split(","));           // ["a", "b", "c"]
console.log(["a", "b", "c"].join("-"));    // "a-b-c"

console.log("hello world".replace("world", "JS"));   // "hello JS" — first match only
console.log("aabbcc".replaceAll("b", "X"));          // "aaXXcc"


// =========================================================
// TEMPLATE LITERALS — backtick strings with expression slots
// =========================================================

const name = "Alice";
const age  = 30;

console.log(`Name: ${name}, Age: ${age}`);
console.log(`3 * 7 = ${3 * 7}`);
console.log(`${age >= 18 ? "adult" : "minor"}`); // expression in slot

// Multi-line — no \n needed
const multiline = `
  Line one
  Line two
  Line three
`.trim();
console.log(multiline);


// =========================================================
// REGULAR EXPRESSIONS — pattern matching
// =========================================================

const text = "The price is $42.00 and $5.99";

// Test — does the pattern exist?
console.log(/\d+/.test(text));           // true

// Match — find first match
const m = text.match(/\$\d+\.\d+/);
console.log(m?.[0]);                     // "$42.00"

// Match all — find every match (g flag = global)
const all = [...text.matchAll(/\$[\d.]+/g)];
console.log(all.map((m) => m[0]));       // ["$42.00", "$5.99"]

// Replace using a regex
console.log("2024-05-11".replace(/(\d{4})-(\d{2})-(\d{2})/, "$3/$2/$1"));
// "11/05/2024"

// Common regex flags
//   g — global (find all, not just first)
//   i — case-insensitive
//   m — multiline (^ and $ match line start/end)

console.log("Hello World".replace(/\b\w/g, (c) => c.toLowerCase())); // "hello world"
