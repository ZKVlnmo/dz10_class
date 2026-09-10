#include<iostream>
#include<thread>
#include<atomic>
//#include<unistd.h>
//#include<lock>
#include<vector>
using namespace std;

vector<int> a;

void threadFunc(int ind, vector<int> &a, vector<vector<int>> &ans) {
    int m = a.size();
    int n = ans[0].size();
    int st = ((m * ind) / n);
    int en = ((m * (ind+1)) / n);
    ans[2][ind] = st;
    for (int i = st; i < min(en, m); ++i) {
        ans[0][ind] += a[i];
        ans[1][ind] += 1 - (a[i] % 2);
        if (a[i] > a[ans[2][ind]]) ans[2][ind] = i;
    }
}

int main () {
    int m = 5, n, otv1 = 0, otv2 = 0, otv3 = 0; cin >> n;
    vector<int> a = {1, 2, 3, 4, 5};
    vector<thread> threads;
    vector<vector<int>>ans(3, vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
        threads.push_back(thread(threadFunc, i, ref(a), ref(ans)));
    for (int i = 0; i < n; ++i)
        threads[i].join();

    
    for (int i = 0; i < n; ++i) {
        cout << ans[0][i] << ' ';
        otv1 += ans[0][i];
    }
    cout << "\notv 1 - " << otv1 << "\n\n";



    for (int i = 0; i < n; ++i) {
        cout << ans[1][i] << ' ';
        otv2 = ans[1][i];
    }
    cout << "\notv 2 - " << otv2 << "\n\n";

    for (int i = 0; i < n; ++i) {
        cout << ans[2][i] << ' ';
        if (a[otv3] < a[ans[2][i]]) otv3 = ans[2][i];
    }
    cout << "\notv 3 - [" << otv3 << "] " << a[otv3] << '\n';


    return 0;
}