// 06 - Arrays and Vectors
// Arrays: fixed-size collections of the same type.
// Vectors: dynamic arrays that can grow/shrink at runtime (prefer these).

#include <iostream>
#include <vector>
#include <algorithm>  // for std::sort, std::find

int main() {

    // =========================================================
    // ARRAYS  (size fixed at compile time)
    // =========================================================
    int scores[5] = {90, 75, 88, 62, 95};

    std::cout << "=== Array ===\n";
    std::cout << "First element : " << scores[0] << "\n"; // index starts at 0
    std::cout << "Last element  : " << scores[4] << "\n";

    // Iterate with a classic for loop
    std::cout << "All scores: ";
    for (int i = 0; i < 5; i++) {
        std::cout << scores[i] << " ";
    }
    std::cout << "\n";

    // 2D array (think: rows x columns)
    int grid[2][3] = {{1, 2, 3}, {4, 5, 6}};
    std::cout << "grid[1][2] = " << grid[1][2] << "\n"; // 6


    // =========================================================
    // VECTORS  (dynamic — preferred in modern C++)
    // =========================================================
    std::vector<int> nums = {5, 3, 8, 1, 9, 2};

    std::cout << "\n=== Vector ===\n";
    std::cout << "Size: " << nums.size() << "\n";

    nums.push_back(7);   // add to the end
    nums.pop_back();     // remove from the end
    std::cout << "After push/pop, size: " << nums.size() << "\n";

    // Range-based for loop (cleaner than index loops)
    std::cout << "Elements: ";
    for (int n : nums) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // Sort ascending
    std::sort(nums.begin(), nums.end());
    std::cout << "Sorted:   ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Find an element
    auto it = std::find(nums.begin(), nums.end(), 8);
    if (it != nums.end()) {
        std::cout << "Found 8 at index " << (it - nums.begin()) << "\n";
    }

    // Insert at position 2
    nums.insert(nums.begin() + 2, 99);
    std::cout << "After inserting 99 at index 2: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Erase element at index 2
    nums.erase(nums.begin() + 2);
    std::cout << "After erasing index 2:         ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
