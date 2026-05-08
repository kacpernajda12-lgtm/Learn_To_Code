// 03 - Operators
// Operators let you do math, compare values, and combine conditions.

#include <iostream>

int main() {
    // --- Arithmetic operators ---
    int a = 10, b = 3;
    std::cout << "=== Arithmetic ===\n";
    std::cout << "a + b = " << (a + b) << "\n";   // 13
    std::cout << "a - b = " << (a - b) << "\n";   // 7
    std::cout << "a * b = " << (a * b) << "\n";   // 30
    std::cout << "a / b = " << (a / b) << "\n";   // 3  (integer division — truncates)
    std::cout << "a % b = " << (a % b) << "\n";   // 1  (remainder / modulo)

    double x = 10.0, y = 3.0;
    std::cout << "x / y = " << (x / y) << "\n";   // 3.333... (floating-point division)

    // --- Assignment shorthand ---
    std::cout << "\n=== Assignment shorthand ===\n";
    int n = 5;
    n += 3;  std::cout << "n += 3  -> " << n << "\n";  // 8
    n -= 2;  std::cout << "n -= 2  -> " << n << "\n";  // 6
    n *= 4;  std::cout << "n *= 4  -> " << n << "\n";  // 24
    n /= 6;  std::cout << "n /= 6  -> " << n << "\n";  // 4
    n %= 3;  std::cout << "n %= 3  -> " << n << "\n";  // 1

    // --- Increment / decrement ---
    std::cout << "\n=== Increment / Decrement ===\n";
    int c = 5;
    std::cout << "c++  -> " << c++ << " (returns old value, then increments)\n"; // 5
    std::cout << "c now: " << c   << "\n";                                        // 6
    std::cout << "++c  -> " << ++c << " (increments first, then returns)\n";     // 7

    // --- Comparison operators (result is bool: true/false) ---
    std::cout << "\n=== Comparisons ===\n";
    std::cout << "10 == 10 : " << (10 == 10) << "\n";  // 1 (true)
    std::cout << "10 != 3  : " << (10 != 3)  << "\n";  // 1 (true)
    std::cout << "10 >  3  : " << (10 >  3)  << "\n";  // 1
    std::cout << "10 <  3  : " << (10 <  3)  << "\n";  // 0 (false)
    std::cout << "10 >= 10 : " << (10 >= 10) << "\n";  // 1
    std::cout << "10 <= 9  : " << (10 <= 9)  << "\n";  // 0

    // --- Logical operators ---
    std::cout << "\n=== Logical ===\n";
    bool p = true, q = false;
    std::cout << "p && q (AND): " << (p && q) << "\n"; // 0 — both must be true
    std::cout << "p || q (OR) : " << (p || q) << "\n"; // 1 — at least one true
    std::cout << "!p     (NOT): " << (!p)      << "\n"; // 0 — flips the value

    return 0;
}
