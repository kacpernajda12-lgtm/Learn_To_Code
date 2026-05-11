// 04 - Control Flow

// =========================================================
// IF / ELSE IF / ELSE
// =========================================================

const score = 75;

if (score >= 90) {
    console.log("A");
} else if (score >= 75) {
    console.log("B");  // prints this
} else if (score >= 60) {
    console.log("C");
} else {
    console.log("F");
}


// =========================================================
// SWITCH — best when comparing one value against many constants
// =========================================================

const day = "Monday";

switch (day) {
    case "Saturday":
    case "Sunday":
        console.log("Weekend");
        break;
    case "Monday":
        console.log("Start of work week"); // prints this
        break;
    case "Friday":
        console.log("Almost weekend");
        break;
    default:
        console.log("Midweek");
}
// break is required — without it, execution "falls through" to the next case


// =========================================================
// WHILE — run while a condition is true
// =========================================================

let count = 0;
while (count < 3) {
    console.log(`while: count = ${count}`);
    count++;
}

// do-while — body always runs at least once
let attempt = 0;
do {
    console.log(`attempt: ${attempt}`);
    attempt++;
} while (attempt < 0); // condition is false immediately, but body ran once


// =========================================================
// FOR — classic counter loop
// =========================================================

for (let i = 0; i < 4; i++) {
    if (i === 2) continue;  // skip 2
    if (i === 4) break;     // never reached here but shows syntax
    console.log(`for: i = ${i}`);  // 0, 1, 3
}


// =========================================================
// FOR...OF — iterate values of an iterable (array, string, Map, Set)
// =========================================================

const fruits = ["apple", "banana", "cherry"];
for (const fruit of fruits) {
    console.log(fruit);
}

// Works on strings too — iterates over characters
for (const char of "hi") {
    console.log(char);  // "h", "i"
}


// =========================================================
// FOR...IN — iterate keys of an object (not recommended for arrays)
// =========================================================

const person = { name: "Alice", age: 30, city: "Warsaw" };
for (const key in person) {
    console.log(`${key}: ${person[key]}`);
}


// =========================================================
// LABELED BREAK — break out of nested loops
// =========================================================

outer: for (let i = 0; i < 3; i++) {
    for (let j = 0; j < 3; j++) {
        if (i === 1 && j === 1) break outer;  // exits both loops
        console.log(`(${i}, ${j})`);
    }
}
// Prints: (0,0) (0,1) (0,2) (1,0)  — stops at (1,1)
