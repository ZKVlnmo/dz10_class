#include<iostream>
#include<thread>
//#include<unistd.h>
//#include<lock>
#include<vector>
using namespace std;

void threadFunc(int ind, vector<int> &a, vector<int> &b, int k) {
    int n = a.size() / 2; //, k = results.size();

    int st = ((n * ind) / k);
    int en = ((n * (ind+1)) / k);

    for (int i = st; i < en; ++i) {
        b[i] = a[i] * a[2*n-i-1];
    }
}

int main () {
    int n; cin >> n;
    int k; cin >> k;

    vector<int> a(n, 1), b(n/2);
    vector<thread> threads;

    for (int i = 0; i < n; ++i) {
        a[i] = 2*i+1;
    }

    for (int i = 0; i < k; ++i)
        threads.push_back(thread(threadFunc, i, ref(a), ref(b), k));
    for (int i = 0; i < k; ++i)
        threads[i].join();

    int s = 0;
    
    for (int i = 0; i < n/2; ++i) {
        s += b[i];
    }

    return 0;
}