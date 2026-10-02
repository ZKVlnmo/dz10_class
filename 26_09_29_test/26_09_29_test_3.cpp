#include <iostream>
#include <vector>
#include <random>
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;

void ftTeradiVRuchki(atomic<int> &teradi, atomic<int> &ruchki) {
    int tvrCount = 1000;
    while (tvrCount >= 0) {
        tvrCount--;
        if (teradi > 0) {
            teradi--; ruchki++;
        }
    }
}

void ftRuchkiVKarandashi(atomic<int> &ruchki, atomic<int> &karandashi) {
    int rvkCount = 1000;
    while (rvkCount >= 0) {
        rvkCount--;
        if (ruchki) {
            ruchki--; karandashi++;
        }
    }
}

void ftPrinter(atomic<int> &teradi, atomic<int> &ruchki, atomic<int> &karandashi) {
    int count = 0;
    while (count < 500) {
        cout << teradi << ' ' << ruchki << ' ' << karandashi << '\n';
    }
}

int main () {
    atomic<int> teradi = 100, ruchki = 100, karandashi = 100;

    thread tTeradiVRuchki(ftTeradiVRuchki, ref(teradi), ref(ruchki));
    thread tRuchkiVKarandashi(ftRuchkiVKarandashi, ref(ruchki), ref(karandashi));
    thread tPrinter(ftPrinter, ref(teradi), ref(ruchki), ref(karandashi));

    tTeradiVRuchki.join();
    tRuchkiVKarandashi.join();

    return 0;
}