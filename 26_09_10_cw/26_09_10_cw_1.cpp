#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

mutex m;
condition_variable cv;
bool ready;

void consumer() {
    unique_lock lock(m);
    cv.wait(lock, [] { return ready; });
    cout << "Я проснулся\n";
}

void producer() {
    cout << "Ждём сигнал\n";
    int a; cin >> a;
    {
        lock_guard lock(m);
        ready = true;
    }
    cout << "Сигнал получен, будем поток\n";
    cv.notify_one();
}

int main () {
    ready = false;
    thread c(consumer), p(producer);
    p.join(); c.join();

    /*cout << ready << '\n';
    
    ready = true;
    cv.notify_one();*/

    return 0;
}