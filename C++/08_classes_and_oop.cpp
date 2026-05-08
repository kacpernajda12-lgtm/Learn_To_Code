// 08 - Classes and Object-Oriented Programming (OOP)
// A class is a blueprint. An object is an instance created from that blueprint.
// Core OOP pillars: Encapsulation, Inheritance, Polymorphism.

#include <iostream>
#include <string>

// =========================================================
// BASE CLASS
// =========================================================
class Animal {
private:
    // Private: only accessible inside this class
    std::string name;
    int         age;

public:
    // Constructor: called automatically when an object is created
    Animal(std::string n, int a) : name(n), age(a) {}

    // Destructor: called automatically when the object is destroyed
    ~Animal() {
        std::cout << name << " is destroyed.\n";
    }

    // Getters (Encapsulation: controlled access to private data)
    std::string getName() const { return name; }
    int         getAge()  const { return age;  }

    // Setter with simple validation
    void setAge(int a) {
        if (a >= 0) age = a;
    }

    // Virtual function: derived classes can override it
    virtual void speak() const {
        std::cout << name << " makes a sound.\n";
    }

    void describe() const {
        std::cout << "Name: " << name << ", Age: " << age << "\n";
    }
};


// =========================================================
// DERIVED CLASS (Inheritance)
// =========================================================
class Dog : public Animal {
private:
    std::string breed;

public:
    Dog(std::string name, int age, std::string breed)
        : Animal(name, age), breed(breed) {}  // call base constructor

    // Override the virtual function (Polymorphism)
    void speak() const override {
        std::cout << getName() << " says: Woof!\n";
    }

    void fetch() const {
        std::cout << getName() << " fetches the ball!\n";
    }
};

class Cat : public Animal {
public:
    Cat(std::string name, int age) : Animal(name, age) {}

    void speak() const override {
        std::cout << getName() << " says: Meow!\n";
    }
};


// =========================================================
// MAIN
// =========================================================
int main() {
    // Stack-allocated objects
    Dog dog("Rex",   3, "Labrador");
    Cat cat("Whiskers", 5);

    dog.describe();
    cat.describe();

    // Polymorphism: base-class pointer calls the right overridden method
    Animal* animals[2] = {&dog, &cat};
    std::cout << "\n--- Polymorphic speak ---\n";
    for (Animal* a : animals) {
        a->speak();  // calls Dog::speak or Cat::speak depending on actual type
    }

    dog.fetch();

    // Heap-allocated object
    Animal* heapDog = new Dog("Buddy", 2, "Beagle");
    heapDog->speak();
    delete heapDog;  // triggers destructor

    return 0;  // stack objects destroyed here — destructors called automatically
}
