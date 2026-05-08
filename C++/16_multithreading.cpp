// 16 - Multithreading (C++11)
// Threads run code concurrently. Shared data must be protected.
// Key tools: std::thread, mutex, condition_variable, atomic, future.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <vector>
#include <chrono>

std::mutex coutMtx;   // protects std::cout (not thread-safe by default)

void safePrint(const std::string& msg) {
    std::lock_guard<std::mutex> lock(coutMtx);
    std::cout << msg << "\n";
}


// =========================================================
// 1. BASIC THREAD
// =========================================================
void worker(int id, int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    safePrint("Thread " + std::to_string(id) + " done (slept " + std::to_string(ms) + "ms)");
}

void demoBasicThreads() {
    std::cout << "=== Basic threads ===\n";
    std::vector<std::thread> threads;

    for (int i = 1; i <= 4; i++) {
        threads.emplace_back(worker, i, i * 50); // pass args after the function
    }

    for (auto& t : threads) t.join(); // wait for all threads to finish
    std::cout << "All threads joined\n\n";
}


// =========================================================
// 2. MUTEX — protect shared state from data races
// =========================================================
std::mutex counterMtx;
int sharedCounter = 0;

void incrementSafe(int times) {
    for (int i = 0; i < times; i++) {
        std::lock_guard<std::mutex> lock(counterMtx); // released when lock goes out of scope
        sharedCounter++;
    }
}

void demoMutex() {
    std::cout << "=== Mutex ===\n";
    sharedCounter = 0;
    std::thread t1(incrementSafe, 10000);
    std::thread t2(incrementSafe, 10000);
    t1.join(); t2.join();
    std::cout << "Counter (expected 20000): " << sharedCounter << "\n\n";
}


// =========================================================
// 3. ATOMIC — lock-free integer operations
// =========================================================
void demoAtomic() {
    std::cout << "=== Atomic ===\n";
    std::atomic<int> atomicCount{0};

    auto inc = [&](int times) {
        for (int i = 0; i < times; i++) atomicCount++;
    };

    std::thread t1(inc, 10000);
    std::thread t2(inc, 10000);
    t1.join(); t2.join();
    std::cout << "Atomic counter (expected 20000): " << atomicCount << "\n\n";
}


// =========================================================
// 4. CONDITION VARIABLE — synchronise producer / consumer
// =========================================================
std::mutex              queueMtx;
std::condition_variable cv;
std::vector<int>        workQueue;
bool                    done = false;

void producer() {
    for (int i = 1; i <= 5; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        {
            std::lock_guard<std::mutex> lock(queueMtx);
            workQueue.push_back(i);
            safePrint("Produced: " + std::to_string(i));
        }
        cv.notify_one(); // wake up the consumer
    }
    {
        std::lock_guard<std::mutex> lock(queueMtx);
        done = true;
    }
    cv.notify_all();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMtx);
        cv.wait(lock, [] { return !workQueue.empty() || done; }); // spurious-wakeup safe

        while (!workQueue.empty()) {
            int item = workQueue.back();
            workQueue.pop_back();
            lock.unlock();
            safePrint("Consumed: " + std::to_string(item));
            lock.lock();
        }
        if (done) break;
    }
}

void demoCondVar() {
    std::cout << "=== Producer / Consumer ===\n";
    done = false;
    workQueue.clear();

    std::thread p(producer);
    std::thread c(consumer);
    p.join(); c.join();
    std::cout << "\n";
}


// =========================================================
// 5. STD::FUTURE / ASYNC — run a task async and get the result
// =========================================================
long long heavyComputation(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) sum += i;
    return sum;
}

void demoFuture() {
    std::cout << "=== std::async / future ===\n";

    // Launch async — may run on a new thread or lazily
    auto fut1 = std::async(std::launch::async, heavyComputation, 1000000);
    auto fut2 = std::async(std::launch::async, heavyComputation, 2000000);

    // Do other work here while computation runs...
    safePrint("Waiting for results...");

    std::cout << "Sum 1M: "  << fut1.get() << "\n"; // blocks until ready
    std::cout << "Sum 2M: "  << fut2.get() << "\n";
}


// =========================================================
int main() {
    demoBasicThreads();
    demoMutex();
    demoAtomic();
    demoCondVar();
    demoFuture();
    return 0;
}
