#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
using namespace std;

void threadFunc(int ind, int k, vector<int> &a, vector<atomic<int>> &otv) {
    int n = a.size();
    int st = ((n * ind) / k);
    int en = ((n * (ind+1)) / k);

    for (int i = st; i < en; ++i) {
        otv[a[i]]++;
    }
}

int main () {
    vector<thread> threads;
    vector<int> a = {5, 2, 5, 3, 2, 5, 2};
    vector<atomic<int>> otv(100);
    for (int i = 0; i < 100; ++i) otv[i] = 0;
    int n = a.size(), k = 3, maxOtv=0;

    for (int i = 0; i < k; ++i)
        threads.push_back(thread(threadFunc, i, k, ref(a), ref(otv)));
    for (int i = 0; i < k; ++i)
        threads[i].join();

    for (int i = 0; i < 100; ++i) {
        //cout << otv[i] << '\n';
        if (otv[maxOtv] < otv[i]) maxOtv = i;
    }

    cout << maxOtv << '\n';
    return 0;
}