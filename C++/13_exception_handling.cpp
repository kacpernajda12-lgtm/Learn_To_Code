// 13 - Exception Handling
// Exceptions separate error-handling code from normal logic.
// Flow: throw → unwind the stack → catch the nearest matching handler.

#include <iostream>
#include <stdexcept>   // standard exception types
#include <string>
#include <memory>

// =========================================================
// CUSTOM EXCEPTION CLASSES
// Inherit from std::exception (or std::runtime_error etc.)
// =========================================================
class AppError : public std::runtime_error {
public:
    explicit AppError(const std::string& msg) : std::runtime_error(msg) {}
};

class NetworkError : public AppError {
private:
    int statusCode;
public:
    NetworkError(const std::string& msg, int code)
        : AppError(msg), statusCode(code) {}
    int getCode() const { return statusCode; }
};

class DatabaseError : public AppError {
public:
    explicit DatabaseError(const std::string& msg) : AppError(msg) {}
};


// =========================================================
// FUNCTIONS THAT THROW
// =========================================================
double divide(double a, double b) {
    if (b == 0.0) throw std::invalid_argument("Division by zero");
    return a / b;
}

int getElement(const std::vector<int>& v, int index) {
    if (index < 0 || index >= static_cast<int>(v.size()))
        throw std::out_of_range("Index " + std::to_string(index) + " is out of range");
    return v[index];
}

void fetchData(const std::string& url) {
    if (url.empty()) throw NetworkError("Empty URL", 400);
    if (url == "bad") throw NetworkError("Server unreachable", 503);
    std::cout << "Fetched data from: " << url << "\n";
}


// =========================================================
// RAII: Resource Acquisition Is Initialization
// Tie resource lifetime to object lifetime so cleanup always runs.
// =========================================================
class ManagedFile {
    std::string name;
public:
    explicit ManagedFile(const std::string& n) : name(n) {
        std::cout << "Opened file: " << name << "\n";
    }
    ~ManagedFile() {
        // Called even if an exception is thrown — no leak
        std::cout << "Closed file: " << name << "\n";
    }
    void write(const std::string& data) {
        std::cout << "Writing '" << data << "' to " << name << "\n";
    }
};


int main() {

    // --- Basic try/catch ---
    std::cout << "=== Basic try/catch ===\n";
    try {
        double result = divide(10.0, 0.0);
        std::cout << "Result: " << result << "\n"; // never reached
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }


    // --- Multiple catch blocks (most specific first) ---
    std::cout << "\n=== Multiple catch blocks ===\n";
    auto tryFetch = [](const std::string& url) {
        try {
            fetchData(url);
        } catch (const NetworkError& e) {
            std::cout << "Network error [" << e.getCode() << "]: " << e.what() << "\n";
        } catch (const AppError& e) {
            std::cout << "App error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "Std error: " << e.what() << "\n";
        }
    };

    tryFetch("https://example.com");
    tryFetch("");
    tryFetch("bad");


    // --- catch(...) catches anything ---
    std::cout << "\n=== catch-all ===\n";
    try {
        throw 42;  // throwing a plain int (unusual but legal)
    } catch (...) {
        std::cout << "Caught something unknown\n";
    }


    // --- Re-throwing an exception ---
    std::cout << "\n=== Re-throw ===\n";
    auto process = []() {
        try {
            throw DatabaseError("Connection lost");
        } catch (const DatabaseError& e) {
            std::cout << "Logging error: " << e.what() << "\n";
            throw; // re-throw the same exception to the outer caller
        }
    };

    try {
        process();
    } catch (const AppError& e) {
        std::cout << "Outer caught: " << e.what() << "\n";
    }


    // --- RAII + exceptions ---
    std::cout << "\n=== RAII + exception ===\n";
    try {
        ManagedFile f("data.txt");
        f.write("hello");
        throw std::runtime_error("Something went wrong mid-operation");
        f.write("this never runs");
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
        // File destructor already ran before this catch — no resource leak
    }


    // --- noexcept: promise that a function never throws ---
    // (used on destructors and move operations for performance)
    auto safeOp = []() noexcept { return 42; };
    std::cout << "\nnoexcept result: " << safeOp() << "\n";

    return 0;
}
