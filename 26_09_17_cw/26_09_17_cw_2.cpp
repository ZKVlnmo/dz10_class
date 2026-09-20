#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <fstream>
#include <atomic>
using namespace std;
//mutex m;
atomic<bool> open;

void threadFunc(int ind, int k) {
    int number, sum;
    bool workaem = true;
    //unique_lock<mutex> lock(m);
    //lock.unlock();
    while (workaem) {
        //lock.lock();
        if (open) {
            open = false;
            ofstream fileOut("26_09_17_cw_2.txt", ios::app);
            //file.open("26_09_17_cw_2.txt", ios::in | ios::out | ios::trunc);
            fileOut << ind << ' ';
            cout << "WRITE: " << ind << '\n'; 
            fileOut.close();

            fstream fileIn("26_09_17_cw_2.txt");
            sum = 0;
            while(fileIn >> number) {
                //cout << number << '\n';
                sum += number;
                cout << "READ: " << number << '\n';
            }
            fileIn.close();
            cout << "SUM: " << sum << '\n';

            if (sum >= ind*k) {
                workaem = false;
                open = true;
                return;
            }
            
            open = true;
            this_thread::sleep_for(chrono::milliseconds(15));
        }
        else {
            this_thread::sleep_for(chrono::milliseconds(10));
        }

    }
}

int main () {
    ofstream("26_09_17_cw_2.txt", ios::trunc).close();
    /*fstream file("26_09_17_cw_2.txt", ios::in | ios::out | ios::trunc);

    if (!file.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return 1;
    }
    file.close();*/

    int k = 4;
    vector<thread> threads;
    open = true;

    for (int i = 0; i < k; ++i)
        threads.push_back(thread(threadFunc, i+1, k));
    for (int i = 0; i < k; ++i)
        threads[i].join();
    
    return 0;
}