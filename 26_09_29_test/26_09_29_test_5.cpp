#include <iostream>
#include <vector>
#include <random>
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;

mutex trans;
vector<int> cifri = {1000, 1000, 1000};

void transfer(int from, int to, int amount) {
    lock_guard lock(trans);
    if (cifri[from] >= amount) {
        cifri[from] -= amount;
        cifri[to] += amount;
    }
    cout << cifri[0] << ' ' << cifri[1] << ' ' << cifri[2] << '\n';
}

void ftA() { while(true) transfer(0, 1, 1); }
void ftB() { while(true) transfer(1, 2, 2); }
void ftC() { while(true) transfer(2, 0, 3); }

int main () {
    thread tA(ftA), tB(ftB), tC(ftC);
    tA.join(); tB.join(); tC.join();

    return 0;
}