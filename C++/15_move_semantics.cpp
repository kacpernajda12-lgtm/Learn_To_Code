// 15 - Move Semantics and Rvalue References (C++11)
// Copying is expensive (duplicates data). Moving is cheap (steals data).
// Use std::move to turn a copy into a move when you no longer need the source.

#include <iostream>
#include <string>
#include <vector>
#include <utility>   // std::move, std::forward

// =========================================================
// A class that manages a heap resource to illustrate the
// Rule of Five: destructor, copy-ctor, copy-assign,
//               move-ctor, move-assign.
// =========================================================
class Buffer {
    int*   data;
    size_t size;

public:
    // Constructor
    explicit Buffer(size_t n) : size(n), data(new int[n]()) {
        std::cout << "Constructed  Buffer[" << size << "]\n";
    }

    // Destructor
    ~Buffer() {
        delete[] data;
        std::cout << "Destroyed    Buffer[" << size << "]\n";
    }

    // Copy constructor — deep copy
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + size, data);
        std::cout << "Copy-constructed Buffer[" << size << "]\n";
    }

    // Copy assignment — deep copy
    Buffer& operator=(const Buffer& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        data = new int[size];
        std::copy(other.data, other.data + size, data);
        std::cout << "Copy-assigned Buffer[" << size << "]\n";
        return *this;
    }

    // Move constructor — steals the resource, leaves source empty
    Buffer(Buffer&& other) noexcept
        : size(other.size), data(other.data) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move-constructed Buffer[" << size << "]\n";
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        size       = other.size;
        data       = other.data;
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move-assigned Buffer[" << size << "]\n";
        return *this;
    }

    void fill(int v) { for (size_t i = 0; i < size; i++) data[i] = v; }
    int  get(size_t i) const { return data[i]; }
    size_t length() const { return size; }
};


// =========================================================
// PERFECT FORWARDING with a variadic factory function
// std::forward<T> preserves lvalue/rvalue category.
// =========================================================
template <typename T, typename... Args>
T create(Args&&... args) {
    return T(std::forward<Args>(args)...);
}


// =========================================================
int main() {

    std::cout << "--- Copy vs Move ---\n";
    Buffer a(4);
    a.fill(7);

    Buffer b = a;               // copy  — expensive, both own data
    Buffer c = std::move(a);    // move  — cheap, a is now empty

    std::cout << "c[0] = " << c.get(0) << "\n";
    // a.data is nullptr — accessing a after move is undefined behaviour

    std::cout << "\n--- Move assignment ---\n";
    Buffer d(8);
    d = std::move(c);           // move-assign: c gives its data to d

    std::cout << "\n--- Vector reallocation uses moves ---\n";
    // std::vector calls move (not copy) on Buffer objects when it resizes,
    // because Buffer declares noexcept move operations.
    std::vector<Buffer> vec;
    vec.reserve(3);
    vec.emplace_back(2);        // construct in-place — no copy, no move
    vec.emplace_back(3);
    vec.emplace_back(4);

    std::cout << "\n--- Perfect forwarding factory ---\n";
    auto s = create<std::string>(5, 'x');   // forward size_t + char to string ctor
    std::cout << "Created string: " << s << "\n";

    std::cout << "\n--- Cleanup ---\n";
    // All Buffers destroyed here in reverse order of construction
    return 0;
}
