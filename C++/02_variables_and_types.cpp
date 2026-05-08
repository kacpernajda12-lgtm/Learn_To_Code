// 02 - Variables and Data Types
// Variables are named boxes that store values.
// Every variable has a type that defines what kind of value it holds.

#include <iostream>
#include <string>

int main() {
    // --- Integer types ---
    int age = 25;               // whole number (positive or negative)
    unsigned int score = 100;   // whole number, never negative
    long bigNumber = 1000000L;  // larger range than int

    // --- Floating-point types ---
    float  pi_f = 3.14f;        // ~7 decimal digits of precision
    double pi_d = 3.14159265;   // ~15 decimal digits of precision (prefer this)

    // --- Character and string ---
    char   letter = 'A';        // single character (use single quotes)
    std::string name = "Alice"; // sequence of characters (use double quotes)

    // --- Boolean ---
    bool isLearning = true;     // true or false

    // --- Printing them ---
    std::cout << "Name:        " << name        << "\n";
    std::cout << "Age:         " << age         << "\n";
    std::cout << "Score:       " << score       << "\n";
    std::cout << "Big number:  " << bigNumber   << "\n";
    std::cout << "Pi (float):  " << pi_f        << "\n";
    std::cout << "Pi (double): " << pi_d        << "\n";
    std::cout << "Letter:      " << letter      << "\n";
    std::cout << "Is learning: " << isLearning  << "\n"; // prints 1 for true, 0 for false

    // --- Constants: values that must not change ---
    const double GRAVITY = 9.81;
    std::cout << "Gravity: " << GRAVITY << " m/s^2\n";

    return 0;
}
