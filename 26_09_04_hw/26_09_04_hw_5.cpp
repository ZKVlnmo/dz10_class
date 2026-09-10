#include<iostream>
#include<thread>
//#include<unistd.h>
//#include<lock>
#include<vector>
using namespace std;

void threadFunc(int ind, vector<vector<int>> &a, vector<vector<int>> &b, int k) {
    int n = a.size();

    int st = ((n * ind) / k);
    int en = ((n * (ind+1)) / k);

    for (int line = st; line < en; ++line) {
        for (int cell = 0; cell < n; ++cell) {
            if (a[line][cell]*1.3 > 255)
                b[line][cell] = 255;
            else
                b[line][cell] = a[line][cell]*1.3;
        }
    }
}

int main () {
    int n; cin >> n;
    int k; cin >> k;

    vector<vector<int>> a(n, vector<int>(n, 0)), b(n, vector<int>(n));
    vector<thread> threads;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = 4;
        }
    }

    for (int i = 0; i < k; ++i)
        threads.push_back(thread(threadFunc, i, ref(a), ref(b), k));
    for (int i = 0; i < k; ++i)
        threads[i].join();

    return 0;
}