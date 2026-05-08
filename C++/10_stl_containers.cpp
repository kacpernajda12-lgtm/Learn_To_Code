// 10 - STL Containers
// The Standard Template Library ships ready-made data structures.
// Pick the right container based on your access/insertion patterns.

#include <iostream>
#include <string>
#include <vector>       // dynamic array
#include <list>         // doubly-linked list
#include <deque>        // double-ended queue
#include <map>          // sorted key→value pairs
#include <unordered_map>// hash map (faster lookup, no order)
#include <set>          // sorted unique values
#include <unordered_set>// hash set
#include <queue>        // FIFO queue / priority queue
#include <stack>        // LIFO stack

void printLine() { std::cout << std::string(40, '-') << "\n"; }

int main() {

    // =========================================================
    // std::list  — O(1) insert/erase anywhere, O(n) random access
    // =========================================================
    printLine();
    std::cout << "std::list\n";
    std::list<int> lst = {3, 1, 4, 1, 5};
    lst.push_front(0);
    lst.push_back(9);
    lst.remove(1);          // removes ALL occurrences of 1
    for (int v : lst) std::cout << v << " ";
    std::cout << "\n";


    // =========================================================
    // std::deque — O(1) push/pop at BOTH ends
    // =========================================================
    printLine();
    std::cout << "std::deque\n";
    std::deque<int> dq = {2, 3, 4};
    dq.push_front(1);
    dq.push_back(5);
    dq.pop_front();
    for (int v : dq) std::cout << v << " ";
    std::cout << "\n";


    // =========================================================
    // std::map  — sorted by key, O(log n) operations
    // =========================================================
    printLine();
    std::cout << "std::map\n";
    std::map<std::string, int> ages;
    ages["Alice"] = 30;
    ages["Bob"]   = 25;
    ages["Carol"] = 28;

    ages.erase("Bob");

    for (auto& [name, age] : ages) {         // structured binding (C++17)
        std::cout << name << ": " << age << "\n";
    }

    // Check key existence before accessing
    if (ages.count("Alice")) {
        std::cout << "Alice's age: " << ages["Alice"] << "\n";
    }


    // =========================================================
    // std::unordered_map — hash map, O(1) average lookup
    // =========================================================
    printLine();
    std::cout << "std::unordered_map (word count)\n";
    std::unordered_map<std::string, int> wordCount;
    std::string words[] = {"apple","banana","apple","cherry","banana","apple"};
    for (const auto& w : words) wordCount[w]++;

    for (auto& [word, count] : wordCount) {
        std::cout << word << ": " << count << "\n";
    }


    // =========================================================
    // std::set  — sorted unique values, O(log n)
    // =========================================================
    printLine();
    std::cout << "std::set\n";
    std::set<int> s = {5, 3, 8, 3, 1, 5};  // duplicates silently dropped
    s.insert(4);
    s.erase(3);
    for (int v : s) std::cout << v << " ";  // always sorted
    std::cout << "\n";


    // =========================================================
    // std::queue  — FIFO (first in, first out)
    // =========================================================
    printLine();
    std::cout << "std::queue\n";
    std::queue<std::string> q;
    q.push("first");
    q.push("second");
    q.push("third");
    while (!q.empty()) {
        std::cout << q.front() << "\n";
        q.pop();
    }


    // =========================================================
    // std::priority_queue — largest element always at the top
    // =========================================================
    printLine();
    std::cout << "std::priority_queue\n";
    std::priority_queue<int> pq;
    pq.push(10); pq.push(30); pq.push(20);
    while (!pq.empty()) {
        std::cout << pq.top() << " ";  // 30, 20, 10
        pq.pop();
    }
    std::cout << "\n";


    // =========================================================
    // std::stack  — LIFO (last in, first out)
    // =========================================================
    printLine();
    std::cout << "std::stack\n";
    std::stack<int> st;
    st.push(1); st.push(2); st.push(3);
    while (!st.empty()) {
        std::cout << st.top() << " ";  // 3, 2, 1
        st.pop();
    }
    std::cout << "\n";

    return 0;
}
