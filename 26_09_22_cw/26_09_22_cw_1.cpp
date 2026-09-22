#include <iostream>
#include <vector>
#include <future>
using namespace std;

int asyncFunc(int ind, int k, vector<int> &a) {
    int otv = 0;
    int n = a.size();
    int st = ((n * ind) / k);
    int en = ((n * (ind+1)) / k);

    for (int i = st; i < en; ++i) {
        otv += a[i];
    }

    return otv;
}

int main() {
    int n = 5, k = 4, otv = 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = 1+(i*5);

    vector<future<int>> res(k);

    for (int i = 0; i < k; ++i)
        res[i] = async(launch::async, asyncFunc, i, k, ref(a));
    for (int i = 0; i < k; ++i)
        otv += res[i].get();

    cout << otv << '\n';
    return 0;
}