// 08 - Classes and Object-Oriented Programming

// =========================================================
// BASE CLASS
// =========================================================

class Animal {
    // Private field — only accessible inside the class body
    #sound;

    // Static property — belongs to the class, not instances
    static kingdom = "Animalia";

    constructor(name, age, sound = "...") {
        this.name  = name;
        this.age   = age;
        this.#sound = sound;
    }

    speak() {
        return `${this.name} says: ${this.#sound}`;
    }

    // Getter — access like a property, not a method call
    get info() {
        return `${this.name} (${this.age} years old)`;
    }

    // toString is called automatically by template literals and string coercion
    toString() {
        return `Animal(${this.name}, ${this.age})`;
    }

    // Factory method — alternative constructor
    static createUnknown() {
        return new Animal("Unknown", 0, "?");
    }
}

const cat = new Animal("Whiskers", 5, "Meow");
console.log(cat.speak());       // "Whiskers says: Meow"
console.log(cat.info);          // "Whiskers (5 years old)"  — getter, no ()
console.log(`${cat}`);          // "Animal(Whiskers, 5)"
console.log(Animal.kingdom);    // "Animalia"
console.log(Animal.createUnknown().speak()); // "Unknown says: ?"


// =========================================================
// INHERITANCE
// =========================================================

class Dog extends Animal {
    #breed;

    constructor(name, age, breed) {
        super(name, age, "Woof");  // must call super() before using 'this'
        this.#breed = breed;
    }

    // Override parent method
    speak() {
        return `${this.name} barks: Woof! Woof!`;
    }

    fetch(item) {
        return `${this.name} fetches the ${item}!`;
    }

    get info() {
        return `${super.info}, breed: ${this.#breed}`;  // extend parent getter
    }
}

class Cat extends Animal {
    constructor(name, age) {
        super(name, age, "Meow~");
    }

    purr() {
        return `${this.name} purrs...`;
    }
}

const dog = new Dog("Rex", 3, "Labrador");
console.log(dog.speak());       // "Rex barks: Woof! Woof!"
console.log(dog.fetch("ball")); // "Rex fetches the ball!"
console.log(dog.info);          // "Rex (3 years old), breed: Labrador"

// instanceof checks inheritance chain
console.log(dog instanceof Dog);    // true
console.log(dog instanceof Animal); // true — Dog IS-A Animal
console.log(dog instanceof Cat);    // false


// =========================================================
// ENCAPSULATION — private fields enforce data hiding
// =========================================================

class BankAccount {
    #balance;
    #owner;

    constructor(owner, initialBalance = 0) {
        this.#owner   = owner;
        this.#balance = initialBalance;
    }

    get balance() {
        return this.#balance;
    }

    deposit(amount) {
        if (amount <= 0) throw new RangeError("Amount must be positive");
        this.#balance += amount;
        return this;                 // enables method chaining
    }

    withdraw(amount) {
        if (amount > this.#balance) throw new RangeError("Insufficient funds");
        this.#balance -= amount;
        return this;
    }

    toString() {
        return `Account(${this.#owner}, $${this.#balance.toFixed(2)})`;
    }
}

const acc = new BankAccount("Alice", 1000);
acc.deposit(500).withdraw(200);  // method chaining
console.log(`${acc}`);           // "Account(Alice, $1300.00)"
console.log(acc.balance);        // 1300

try {
    acc.withdraw(9999);
} catch (e) {
    console.log(`Error: ${e.message}`); // "Error: Insufficient funds"
}


// =========================================================
// POLYMORPHISM — same interface, different behavior
// =========================================================

const animals = [
    new Dog("Rex", 3, "Labrador"),
    new Cat("Luna", 2),
    Animal.createUnknown(),
];

for (const animal of animals) {
    console.log(animal.speak()); // each class has its own speak()
}
