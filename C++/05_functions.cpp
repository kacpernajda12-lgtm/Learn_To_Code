// 05 - Functions
// A function is a named, reusable block of code.
// Structure:  return_type  name(parameters) { body }

#include <iostream>

// --- Function with no parameters and no return value ---
void greet() {
    std::cout << "Hello from a function!\n";
}

// --- Function that takes parameters and returns a value ---
int add(int a, int b) {
    return a + b;
}

// --- Default parameter: used when caller doesn't supply it ---
void printMessage(std::string msg, int times = 1) {
    for (int i = 0; i < times; i++) {
        std::cout << msg << "\n";
    }
}

// --- Function overloading: same name, different parameter types ---
double multiply(double a, double b) { return a * b; }
int    multiply(int    a, int    b) { return a * b; }

// --- Pass by value vs pass by reference ---
void doubleValue(int  x) { x *= 2; }          // copy — original unchanged
void doubleRef  (int& x) { x *= 2; }          // reference — original changes

// --- Recursive function: calls itself ---
int factorial(int n) {
    if (n <= 1) return 1;                      // base case — stops the recursion
    return n * factorial(n - 1);               // recursive case
}

// =========================================================
int main() {
    greet();

    int sum = add(7, 3);
    std::cout << "7 + 3 = " << sum << "\n";

    printMessage("Hello");           // times defaults to 1
    printMessage("Learning C++", 3); // prints 3 times

    std::cout << "multiply(2.5, 4.0) = " << multiply(2.5, 4.0) << "\n";
    std::cout << "multiply(3,   5)   = " << multiply(3,   5)   << "\n";

    int val = 10;
    doubleValue(val);
    std::cout << "After doubleValue: " << val << "\n"; // still 10

    doubleRef(val);
    std::cout << "After doubleRef:   " << val << "\n"; // now 20

    std::cout << "5! = " << factorial(5) << "\n"; // 120

    return 0;
}
