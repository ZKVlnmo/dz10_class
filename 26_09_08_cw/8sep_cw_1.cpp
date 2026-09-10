#include<iostream>
#include<thread>
//#include<unistd.h>
//#include<lock>
#include<vector>
using namespace std;

void threadFunc(int ind, vector<int> &a, vector<int> &b, vector<int> &c, int k) {
    int n = a.size();//, k = results.size();

    int st = ((n * ind) / k);
    int en = ((n * (ind+1)) / k);

    for (int i = st; i < en; ++i) {
        c[i] = 3*a[i] - 2*b[i] + 5;
    }
}

int main () {
    int n; cin >> n;
    int k; cin >> k;

    vector<int> a(n, 1), b(n, 2), c(n, 0);
    vector<thread> threads;

    for (int i = 0; i < k; ++i)
        threads.push_back(thread(threadFunc, i, ref(a), ref(b), ref(c), k));
    for (int i = 0; i < k; ++i)
        threads[i].join();

    return 0;
}