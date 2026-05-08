// 04 - Control Flow
// Control flow decides WHICH code runs and WHEN.

#include <iostream>

int main() {

    // =========================================================
    // IF / ELSE IF / ELSE
    // =========================================================
    int temperature = 22;

    if (temperature > 30) {
        std::cout << "It's hot outside.\n";
    } else if (temperature > 15) {
        std::cout << "Nice weather.\n";       // <-- this branch runs
    } else {
        std::cout << "It's cold outside.\n";
    }

    // --- Ternary operator: compact if/else for single values ---
    std::string verdict = (temperature > 20) ? "warm" : "cool";
    std::cout << "The weather is " << verdict << ".\n";


    // =========================================================
    // SWITCH
    // Best when comparing one variable against fixed values.
    // =========================================================
    int day = 3; // 1 = Monday, 7 = Sunday

    switch (day) {
        case 1: std::cout << "Monday\n";    break;
        case 2: std::cout << "Tuesday\n";   break;
        case 3: std::cout << "Wednesday\n"; break; // <-- runs
        case 4: std::cout << "Thursday\n";  break;
        case 5: std::cout << "Friday\n";    break;
        default: std::cout << "Weekend!\n"; break; // runs if no case matches
    }
    // "break" stops execution from falling through to the next case.


    // =========================================================
    // WHILE loop — runs as long as condition is true
    // =========================================================
    std::cout << "\nCounting up with while:\n";
    int i = 1;
    while (i <= 5) {
        std::cout << i << " ";
        i++;
    }
    std::cout << "\n";


    // =========================================================
    // DO-WHILE loop — always runs the body at least once
    // =========================================================
    std::cout << "\nDo-while (starts at 10, condition already false):\n";
    int j = 10;
    do {
        std::cout << j << " "; // prints 10 even though j > 5
        j++;
    } while (j <= 5);
    std::cout << "\n";


    // =========================================================
    // FOR loop — best when you know the iteration count
    // =========================================================
    std::cout << "\nCounting down with for:\n";
    for (int k = 5; k >= 1; k--) {
        std::cout << k << " ";
    }
    std::cout << "\n";


    // =========================================================
    // BREAK and CONTINUE
    // =========================================================
    std::cout << "\nBreak at 4:\n";
    for (int n = 1; n <= 10; n++) {
        if (n == 4) break;        // exit the loop entirely
        std::cout << n << " ";
    }
    std::cout << "\n";

    std::cout << "\nSkip even numbers with continue:\n";
    for (int n = 1; n <= 10; n++) {
        if (n % 2 == 0) continue; // skip to next iteration
        std::cout << n << " ";
    }
    std::cout << "\n";

    return 0;
}
