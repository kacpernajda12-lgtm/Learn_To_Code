// 09 - Templates
// Templates let you write code that works with any data type.
// The compiler generates a concrete version for each type you use.

#include <iostream>
#include <string>
#include <vector>

// =========================================================
// FUNCTION TEMPLATE
// =========================================================
template <typename T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}

// Multiple type parameters
template <typename T, typename U>
void printPair(T first, U second) {
    std::cout << "(" << first << ", " << second << ")\n";
}

// Template specialisation: custom behaviour for one specific type
template <>
std::string maxOf(std::string a, std::string b) {
    // For strings, compare lengths instead of lexicographic order
    return (a.size() >= b.size()) ? a : b;
}


// =========================================================
// CLASS TEMPLATE
// =========================================================
template <typename T>
class Stack {
private:
    std::vector<T> data;

public:
    void push(const T& item) {
        data.push_back(item);
    }

    void pop() {
        if (!data.empty()) data.pop_back();
    }

    T top() const {
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    int size() const {
        return static_cast<int>(data.size());
    }
};


// =========================================================
// NON-TYPE TEMPLATE PARAMETER
// The value (not just the type) can be a compile-time constant.
// =========================================================
template <typename T, int SIZE>
class FixedArray {
private:
    T arr[SIZE];

public:
    T& operator[](int i)       { return arr[i]; }
    int size() const           { return SIZE; }
};


// =========================================================
int main() {
    // Function template — compiler deduces T automatically
    std::cout << "=== Function templates ===\n";
    std::cout << "max(3, 7)        = " << maxOf(3, 7)           << "\n";
    std::cout << "max(3.5, 2.1)    = " << maxOf(3.5, 2.1)       << "\n";
    std::cout << "max(hi, hello)   = " << maxOf<std::string>("hi","hello") << "\n";

    printPair(42, "answer");
    printPair(3.14, true);

    // Class template
    std::cout << "\n=== Stack<int> ===\n";
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    std::cout << "Top: " << intStack.top() << "\n"; // 30
    intStack.pop();
    std::cout << "Top after pop: " << intStack.top() << "\n"; // 20
    std::cout << "Size: " << intStack.size() << "\n";

    Stack<std::string> strStack;
    strStack.push("hello");
    strStack.push("world");
    std::cout << "\nString stack top: " << strStack.top() << "\n";

    // Non-type parameter
    std::cout << "\n=== FixedArray<double, 4> ===\n";
    FixedArray<double, 4> fa;
    fa[0] = 1.1; fa[1] = 2.2; fa[2] = 3.3; fa[3] = 4.4;
    for (int i = 0; i < fa.size(); i++) std::cout << fa[i] << " ";
    std::cout << "\n";

    return 0;
}
