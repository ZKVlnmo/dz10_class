#include<iostream>
#include<thread>
//#include<unistd.h>
//#include<lock>
#include<vector>
using namespace std;

void threadFunc(int ind, vector<int> &a, vector<int> &b, vector<int> &c) {
    int n = a.size();//, k = results.size();
    int k = c.size();

    int st = ((n * ind) / k);
    int en = ((n * (ind+1)) / k);

    for (int i = st; i < en; ++i) {
        c[ind] += a[i] + b[i];
    }
}

int main () {
    int n; cin >> n;
    int k; cin >> k;

    vector<int> a(n, 1), b(n, 2), c(k, 0);
    vector<thread> threads;

    for (int i = 0; i < k; ++i)
        threads.push_back(thread(threadFunc, i, ref(a), ref(b), ref(c)));
    for (int i = 0; i < k; ++i)
        threads[i].join();

    int s = 0;

    for (int i = 0; i < k; ++i)
        s += c[i];

    cout << s << '\n';

    return 0;
}