#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mutex;
void say_hi(const unsigned int id) {
    auto lock = std::unique_lock{mutex};
    std::cout << "Hello from thread: " << id << std::endl;
}

int main() {
    auto threads = std::vector<std::thread>{};

    for (unsigned int i = 0; i < 10; ++i) { threads.emplace_back(say_hi, i); }

    for (auto &thread: threads) { thread.join(); }

    return 0;
}