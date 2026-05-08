// 12 - Lambdas and STL Algorithms
// A lambda is an anonymous function defined inline.
// STL algorithms (sort, find_if, transform...) accept them as callbacks.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // sort, find_if, count_if, for_each, transform, remove_if
#include <numeric>    // accumulate, iota
#include <functional> // std::function

// =========================================================
// LAMBDA SYNTAX:
//   [ capture ] ( params ) -> return_type { body }
//   capture  — which outer variables to bring in
//   return_type is optional (usually deduced)
// =========================================================

int main() {

    // --- Basic lambda ---
    auto greet = []() { std::cout << "Hello from a lambda!\n"; };
    greet();

    // --- Lambda with parameters and return value ---
    auto add = [](int a, int b) { return a + b; };
    std::cout << "3 + 4 = " << add(3, 4) << "\n";

    // --- Capture by value [=] ---
    int multiplier = 3;
    auto times = [multiplier](int x) { return x * multiplier; };
    std::cout << "5 * 3 = " << times(5) << "\n";

    // --- Capture by reference [&] — can modify outer variable ---
    int counter = 0;
    auto increment = [&counter]() { counter++; };
    increment(); increment(); increment();
    std::cout << "counter = " << counter << "\n"; // 3

    // --- Mutable lambda: modify a by-value capture ---
    int base = 10;
    auto mutableLambda = [base]() mutable {
        base += 5;          // modifies the local copy, not the outer base
        return base;
    };
    std::cout << "mutable lambda: " << mutableLambda() << "\n"; // 15
    std::cout << "outer base unchanged: " << base << "\n";       // 10

    // --- Store in std::function for deferred/repeated calls ---
    std::function<bool(int)> isEven = [](int n) { return n % 2 == 0; };
    std::cout << "isEven(4): " << isEven(4) << "\n";


    // =========================================================
    // STL ALGORITHMS WITH LAMBDAS
    // =========================================================
    std::vector<int> nums = {5, 2, 8, 1, 9, 3, 7, 4, 6};

    // sort — ascending
    std::sort(nums.begin(), nums.end());
    std::cout << "\nSorted: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // sort — descending with lambda comparator
    std::sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });
    std::cout << "Desc:   ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // for_each
    std::cout << "Doubled: ";
    std::for_each(nums.begin(), nums.end(), [](int n) { std::cout << n * 2 << " "; });
    std::cout << "\n";

    // find_if — first element matching a predicate
    auto it = std::find_if(nums.begin(), nums.end(), [](int n) { return n < 4; });
    if (it != nums.end()) std::cout << "First < 4: " << *it << "\n";

    // count_if
    int evenCount = std::count_if(nums.begin(), nums.end(), isEven);
    std::cout << "Even count: " << evenCount << "\n";

    // transform — apply a function to each element, store result
    std::vector<int> squares(nums.size());
    std::transform(nums.begin(), nums.end(), squares.begin(),
                   [](int n) { return n * n; });
    std::cout << "Squares: ";
    for (int n : squares) std::cout << n << " ";
    std::cout << "\n";

    // remove_if + erase idiom (erase-remove idiom)
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    v.erase(std::remove_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; }), v.end());
    std::cout << "Odd only: ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n";

    // accumulate — fold/reduce
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << "Sum: " << sum << "\n";

    int product = std::accumulate(nums.begin(), nums.end(), 1,
                                  [](int acc, int n) { return acc * n; });
    std::cout << "Product: " << product << "\n";

    // iota — fill with sequential values
    std::vector<int> seq(10);
    std::iota(seq.begin(), seq.end(), 1);  // 1, 2, 3, ..., 10
    std::cout << "iota: ";
    for (int n : seq) std::cout << n << " ";
    std::cout << "\n";

    // --- Lambda returning a lambda (factory) ---
    auto makeAdder = [](int offset) {
        return [offset](int x) { return x + offset; };
    };
    auto add10 = makeAdder(10);
    auto add25 = makeAdder(25);
    std::cout << "add10(5) = " << add10(5) << "\n"; // 15
    std::cout << "add25(5) = " << add25(5) << "\n"; // 30

    return 0;
}
