// 11 - Modules
//
// ES Modules split your code into files — each file has its own scope.
// Nothing is shared unless explicitly exported and imported.
//
// To use ES modules with Node.js either:
//   a) name the file with .mjs extension, or
//   b) add "type": "module" to your package.json
//
// This file shows the syntax with runnable examples using inline comments.
// For a real demo, see the /modules_demo/ folder pattern below.


// =========================================================
// NAMED EXPORTS — export multiple things from one file
// =========================================================

// math.js would contain:
//   export const PI = 3.14159;
//   export function add(a, b) { return a + b; }
//   export function multiply(a, b) { return a * b; }

// Importing named exports:
//   import { PI, add, multiply } from "./math.js";
//   import { add as sum } from "./math.js";    // rename on import
//   import * as Math from "./math.js";          // import everything as a namespace


// =========================================================
// DEFAULT EXPORT — one main thing per file
// =========================================================

// logger.js would contain:
//   export default function log(msg) {
//       console.log(`[LOG] ${msg}`);
//   }

// Importing the default export (any name works):
//   import log from "./logger.js";
//   import myLogger from "./logger.js";  // same thing, different local name


// =========================================================
// RE-EXPORTING — barrel files (index.js) aggregate exports
// =========================================================

// index.js:
//   export { add, multiply } from "./math.js";
//   export { default as log } from "./logger.js";

// Consumer just imports from the barrel:
//   import { add, log } from "./index.js";


// =========================================================
// DYNAMIC IMPORT — load modules on demand (returns a Promise)
// =========================================================

// Useful for code splitting: only load heavy modules when needed
//
//   async function loadChart() {
//       const { Chart } = await import("./chart.js");
//       const chart = new Chart(data);
//   }


// =========================================================
// COMMONJS (Node.js legacy) — you'll see this in older code
// =========================================================

// CommonJS uses require() and module.exports instead of import/export
//
//   // math.js (CommonJS)
//   module.exports = { add, multiply };
//
//   // app.js (CommonJS)
//   const { add } = require("./math.js");
//
// ES Modules are the modern standard; prefer them in new code.


// =========================================================
// RUNNABLE DEMO — simulating modules in one file
// =========================================================

// Simulate what a "math module" would export
const mathModule = (() => {
    const PI = 3.14159;
    const add      = (a, b) => a + b;
    const multiply = (a, b) => a * b;
    const circle   = { area: (r) => PI * r * r };
    return { PI, add, multiply, circle };
})();

// Simulate what the consumer file would do with the import
const { PI, add, multiply, circle } = mathModule;

console.log(PI);                // 3.14159
console.log(add(2, 3));         // 5
console.log(multiply(4, 5));    // 20
console.log(circle.area(7).toFixed(2)); // 153.94
