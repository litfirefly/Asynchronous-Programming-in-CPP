// By shared variable or by reference argument

#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

namespace {
int result = 0;
std::mutex mtx;
};  // namespace

void func(int& result) {
    // Simulate some work and return random value in range [1,10]
    std::this_thread::sleep_for(std::chrono::seconds(1));
    result = 1 + (rand() % 10);
}

void funcWithMutex() {
    // Simulating some computation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int localVar = 1 + (rand() % 10);

    // Lock the mutex before updating the shared variable
    std::lock_guard<std::mutex> lock(mtx);
    result = localVar;
}

int main() {
    // Get result value by reference
    std::thread t1(func, std::ref(result));
    t1.join();
    std::cout << "T1 result: " << result << std::endl;

    // Get result value by lambda capture
    std::thread t2([&]() { func(result); });
    t2.join();
    std::cout << "T2 result: " << result << std::endl;

    // Get result value by shared variable and mutex
    std::thread t3(funcWithMutex);
    t3.join();
    std::cout << "T3 result: " << result << std::endl;

    return 0;
}
