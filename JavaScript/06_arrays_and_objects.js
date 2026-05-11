// 06 - Arrays and Objects

// =========================================================
// ARRAYS
// =========================================================

const fruits = ["apple", "banana", "cherry"];

console.log(fruits[0]);          // "apple"
console.log(fruits.length);      // 3
console.log(fruits.at(-1));      // "cherry" — negative index from end

// Mutating methods (change the original array)
fruits.push("date");             // add to end
fruits.pop();                    // remove from end → "date"
fruits.unshift("avocado");       // add to start
fruits.shift();                  // remove from start → "avocado"
fruits.splice(1, 1);             // remove 1 element at index 1

// Non-mutating methods (return a new array)
const upper = fruits.map((f) => f.toUpperCase());
console.log(upper);              // ["APPLE", "CHERRY"]

const long = fruits.filter((f) => f.length > 5);
console.log(long);               // ["cherry"]

const found = fruits.find((f) => f.startsWith("c"));
console.log(found);              // "cherry"

console.log(fruits.includes("apple")); // true
console.log(fruits.indexOf("apple"));  // 0

// Sorting — default sort is lexicographic (alphabetical)
const nums = [10, 2, 30, 1];
nums.sort((a, b) => a - b);            // ascending numeric sort
console.log(nums);   // [1, 2, 10, 30]

// Combining arrays
const a = [1, 2];
const b = [3, 4];
console.log([...a, ...b]);            // [1, 2, 3, 4]
console.log(a.concat(b));             // [1, 2, 3, 4]

// Flatten nested arrays
const nested = [1, [2, 3], [4, [5]]];
console.log(nested.flat());           // [1, 2, 3, 4, [5]]
console.log(nested.flat(Infinity));   // [1, 2, 3, 4, 5]


// =========================================================
// OBJECTS
// =========================================================

const person = {
    name: "Alice",
    age: 30,
    greet() {                          // method shorthand
        return `Hi, I'm ${this.name}`;
    },
};

console.log(person.name);             // dot notation
console.log(person["age"]);           // bracket notation (useful for dynamic keys)
console.log(person.greet());

// Add / update / delete properties
person.city = "Warsaw";
person.age  = 31;
delete person.city;

// Object methods
console.log(Object.keys(person));     // ["name", "age", "greet"]
console.log(Object.values(person));   // ["Alice", 31, fn]
console.log(Object.entries(person));  // [["name","Alice"], ["age",31], ...]

// Copying objects (shallow)
const copy = { ...person };          // spread — top-level properties only
const deep = JSON.parse(JSON.stringify(person)); // deep copy (loses functions)


// =========================================================
// DESTRUCTURING — extract values into named variables
// =========================================================

// Array destructuring
const [first, second, , fourth = "default"] = ["a", "b", "c"];
console.log(first, second, fourth);  // "a" "b" "default"

// Swap variables without a temp
let x = 1, y = 2;
[x, y] = [y, x];
console.log(x, y);  // 2 1

// Object destructuring
const { name, age, city = "Unknown" } = person;
console.log(name, age, city);  // "Alice" 31 "Unknown"

// Rename during destructuring
const { name: fullName } = person;
console.log(fullName); // "Alice"

// Nested destructuring
const config = { db: { host: "localhost", port: 5432 } };
const { db: { host, port } } = config;
console.log(host, port); // "localhost" 5432

// Rest in destructuring
const [head, ...tail] = [1, 2, 3, 4];
console.log(head);  // 1
console.log(tail);  // [2, 3, 4]

const { name: pName, ...rest } = person;
console.log(pName);  // "Alice"
console.log(rest);   // { age: 31 }
