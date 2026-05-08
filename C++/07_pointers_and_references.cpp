// 07 - Pointers and References
// A pointer stores the memory address of another variable.
// A reference is an alias — another name for the same variable.

#include <iostream>

int main() {

    // =========================================================
    // REFERENCES  (simpler, safer — prefer over raw pointers)
    // =========================================================
    int value = 42;
    int& ref = value;   // ref IS value — same memory location

    ref = 100;
    std::cout << "value after ref = 100: " << value << "\n"; // 100


    // =========================================================
    // POINTERS
    // =========================================================
    int x = 10;
    int* ptr = &x;  // ptr holds the ADDRESS of x
                    // &  = "address-of" operator
                    // *  = "dereference" operator (access the value at the address)

    std::cout << "\n=== Pointer basics ===\n";
    std::cout << "x         = " << x    << "\n";   // 10
    std::cout << "&x (addr) = " << ptr  << "\n";   // e.g. 0x61fe14
    std::cout << "*ptr      = " << *ptr << "\n";   // 10  (dereference)

    *ptr = 99;  // change x through the pointer
    std::cout << "x after *ptr = 99: " << x << "\n"; // 99


    // =========================================================
    // NULLPTR — a pointer that points to nothing
    // Always initialise pointers to nullptr if not assigned yet.
    // =========================================================
    int* empty = nullptr;
    if (empty == nullptr) {
        std::cout << "\nPointer is null — safe to check before use.\n";
    }


    // =========================================================
    // POINTERS AND ARRAYS
    // Array names decay to a pointer to their first element.
    // =========================================================
    int arr[3] = {10, 20, 30};
    int* p = arr;       // points to arr[0]

    std::cout << "\n=== Pointer arithmetic ===\n";
    std::cout << "*p       = " << *p       << "\n"; // 10
    std::cout << "*(p+1)   = " << *(p + 1) << "\n"; // 20
    std::cout << "*(p+2)   = " << *(p + 2) << "\n"; // 30


    // =========================================================
    // DYNAMIC MEMORY  (heap allocation)
    // Use new/delete when you need memory whose lifetime you control.
    // =========================================================
    int* heap = new int(55);    // allocate one int on the heap
    std::cout << "\nHeap value: " << *heap << "\n";
    delete heap;                // ALWAYS free what you allocate
    heap = nullptr;             // prevent dangling pointer

    int* arr2 = new int[4]{1, 2, 3, 4};  // heap array
    std::cout << "Heap array: ";
    for (int i = 0; i < 4; i++) std::cout << arr2[i] << " ";
    std::cout << "\n";
    delete[] arr2;  // use delete[] for arrays
    arr2 = nullptr;

    return 0;
}
