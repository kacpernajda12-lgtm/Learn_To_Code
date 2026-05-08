// 11 - Smart Pointers
// Smart pointers wrap raw pointers and automatically free memory
// when it is no longer needed — no manual delete required.
//
// Rule of thumb:
//   unique_ptr  — sole owner (most common)
//   shared_ptr  — shared ownership (ref-counted)
//   weak_ptr    — observe without owning (breaks cycles)

#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Resource {
    std::string name;
    Resource(std::string n) : name(n) {
        std::cout << "Resource '" << name << "' created\n";
    }
    ~Resource() {
        std::cout << "Resource '" << name << "' destroyed\n";
    }
    void use() const {
        std::cout << "Using '" << name << "'\n";
    }
};


// =========================================================
// UNIQUE_PTR — one owner at a time
// =========================================================
void demoUniquePtr() {
    std::cout << "=== unique_ptr ===\n";

    // Prefer make_unique (C++14) — exception-safe and cleaner
    auto ptr = std::make_unique<Resource>("File");

    ptr->use();
    std::cout << "Is null? " << (ptr == nullptr) << "\n";

    // Transfer ownership with std::move — ptr becomes null after this
    auto ptr2 = std::move(ptr);
    std::cout << "ptr null after move? " << (ptr == nullptr) << "\n";
    ptr2->use();

    // Unique pointer to an array
    auto arr = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; i++) arr[i] = i * 10;
    for (int i = 0; i < 5; i++) std::cout << arr[i] << " ";
    std::cout << "\n";

    // ptr2 destroyed here — Resource freed automatically
}


// =========================================================
// SHARED_PTR — multiple owners, freed when last one releases it
// =========================================================
void demoSharedPtr() {
    std::cout << "\n=== shared_ptr ===\n";

    auto sp1 = std::make_shared<Resource>("Database");
    std::cout << "Ref count: " << sp1.use_count() << "\n"; // 1

    {
        auto sp2 = sp1;  // both point to the same Resource
        auto sp3 = sp1;
        std::cout << "Ref count: " << sp1.use_count() << "\n"; // 3
        sp2->use();
    } // sp2, sp3 go out of scope — count drops to 1

    std::cout << "Ref count after block: " << sp1.use_count() << "\n"; // 1
    // Resource freed when sp1 goes out of scope
}


// =========================================================
// WEAK_PTR — observe a shared_ptr without affecting ref count
// Use to break circular references that would cause memory leaks.
// =========================================================
void demoWeakPtr() {
    std::cout << "\n=== weak_ptr ===\n";

    auto sp = std::make_shared<Resource>("Cache");
    std::weak_ptr<Resource> wp = sp;

    std::cout << "Ref count (weak doesn't add): " << sp.use_count() << "\n"; // 1

    // Must lock() to use — lock() returns a temporary shared_ptr
    if (auto locked = wp.lock()) {
        locked->use();
        std::cout << "Ref count while locked: " << locked.use_count() << "\n"; // 2
    }

    sp.reset(); // release the shared_ptr
    std::cout << "expired after reset? " << wp.expired() << "\n"; // 1 (true)
}


// =========================================================
// PRACTICAL: store polymorphic objects safely in a vector
// =========================================================
struct Shape {
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

struct Circle  : Shape { void draw() const override { std::cout << "Drawing Circle\n";  } };
struct Square  : Shape { void draw() const override { std::cout << "Drawing Square\n";  } };
struct Triangle: Shape { void draw() const override { std::cout << "Drawing Triangle\n";} };

void demoPolymorphicVector() {
    std::cout << "\n=== polymorphic vector of unique_ptrs ===\n";

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Square>());
    shapes.push_back(std::make_unique<Triangle>());

    for (const auto& s : shapes) s->draw();
    // All shapes destroyed automatically when vector goes out of scope
}


int main() {
    demoUniquePtr();
    demoSharedPtr();
    demoWeakPtr();
    demoPolymorphicVector();
    return 0;
}
