#include <iostream>
#include <vector>
#include <random>
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;

mutex m;
std::mt19937 generator(std::random_device{}());
std::uniform_int_distribution<int> distribution(0, 9);

void threadFunc(int ind, int &tick, atomic<int> &fails, vector<pair<int, int>> &otv) {
    while(tick <= 100) {

        if (distribution(generator) == 0) {
            fails++;
        }
        else {
            {
                lock_guard lock(m);
                otv.push_back({ind, tick});
                tick++;
            }
            std::this_thread::sleep_for(
                std::chrono::milliseconds(10)
            );
        }
    }
}

int main () {
    int k = 5, tick=1;
    atomic<int> fails; fails.store(1);
    vector<thread> threads;
    vector<pair<int, int>> otv;

    for (int i = 0; i < k; ++i)
        threads.push_back(thread(threadFunc, i, ref(tick), ref(fails), ref(otv)));
    for (int i = 0; i < k; ++i)
        threads[i].join();
    

    cout << "Удачно: 100 и Неудачно: " << fails << '\n';
    return 0;
}