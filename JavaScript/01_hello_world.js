// 01 - Hello World
// The simplest JavaScript program: print text to the console.
// Run with: node 01_hello_world.js

console.log("Hello, World!");

// console.log accepts multiple arguments — prints them space-separated
console.log("My", "name", "is", "JavaScript");

// Template literals use backticks and ${} for interpolation
const language = "JavaScript";
console.log(`Hello from ${language}!`);

// Expressions inside ${} are evaluated
console.log(`2 + 2 = ${2 + 2}`);

// console.log can print any value: numbers, booleans, objects
console.log(42);
console.log(true);
console.log({ name: "Alice", age: 30 });
console.log([1, 2, 3]);
