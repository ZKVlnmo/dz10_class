#include<iostream>
#include<thread>
//#include<unistd.h>
//#include<lock>
#include<vector>
using namespace std;

void threadFunc(int line, vector<vector<int>> &a, vector<vector<int>> &b, vector<vector<int>> &c) {
    int n = a.size();
    int m = a[0].size();
    int k = b[0].size();

    for (int cell = 0; cell < k; ++cell) {
        int sam = 0;

        for (int t = 0; t < m; ++t)
            sam += a[line][t] * b[t][cell];
        
        cout << sam << ' ';
        c[line][cell] = sam;
    }
    cout << '\n';
}

int main () {
    int n=3, m=3, k=1;
    vector<vector<int>> a(n, vector<int>(m, 0));
    vector<vector<int>> b(m, vector<int>(k, 0));
    vector<vector<int>> c(n, vector<int>(k, 0));

    cout << "A\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = (i+1)*(j+1);
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "\nB\n";

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            b[i][j] = 1;
            cout << b[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "\nC\n";

    vector<thread> threads;

    for (int i = 0; i < n; ++i)
        threads.push_back(thread(threadFunc, i, ref(a), ref(b), ref(c)));
    for (int i = 0; i < n; ++i)
        threads[i].join();

    return 0;
}