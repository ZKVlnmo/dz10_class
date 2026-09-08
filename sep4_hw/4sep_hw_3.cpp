#include<iostream>
#include<thread>
//#include<unistd.h>
//#include<lock>
#include<vector>
using namespace std;

void threadFunc(int ind, vector<vector<int>> &a, vector<vector<int>> &b, vector<vector<int>> &c, int k) {
    int n = a.size()-2;

    int st = ((n * ind) / k);
    int en = ((n * (ind+1)) / k);

    for (int line = st+1; line < en+1; ++line) {
        for (int cell = 1; cell <= n; ++cell) {
            int sam = 0;

            for (int i : {-1, 0, 1})
                for (int j : {-1, 0, 1})
                    sam += a[line+i][cell+j] * b[1+i][1+j];
            
            c[line-1][cell-1] = sam;
        }
    }
}

int main () {
    int n; cin >> n;
    int k; cin >> k;

    vector<vector<int>> a(n+2, vector<int>(n+2, 0)), b(3, vector<int>(3, 2)), c(n, vector<int>(n, 0));
    vector<thread> threads;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            a[i][j] = 1;
        }
    }

    for (int i = 0; i < k; ++i)
        threads.push_back(thread(threadFunc, i, ref(a), ref(b), ref(c), k));
    for (int i = 0; i < k; ++i)
        threads[i].join();

    return 0;
}