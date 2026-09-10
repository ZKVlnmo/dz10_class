#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cmath>

using namespace std;

void f(vector<double>& c, int thread_id, vector<vector<int>> &a, int c1) {
    int start_row = thread_id * c1;
    int end_row = start_row + c1;

    for (int i = start_row; i < end_row; i++) {
        c[i] = sqrt(a[i][0] * a[i][0] + a[i][1] * a[i][1] + a[i][2] * a[i][2]);
    }
}

void f1(vector<double>& c, int thread_id, vector<vector<int>> &a, int c2) {
    int start_row = a.size() - c2; 
    int end_row = a.size();

    for (int i = start_row; i < end_row; i++) {
        c[i] = sqrt(a[i][0] * a[i][0] + a[i][1] * a[i][1] + a[i][2] * a[i][2]);
    }
}

int main() {
    int n;
    int m;
    int k;
    int count;
    cout << "Write n: ";
    cin >> n;
    cout << "Write m: ";
    cin >> m;
    cout << "Write k: ";
    cin >> k;
    cout << "Write count of threads: ";
    cin >> count;

    vector<vector<int>> a(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
        a[i][0] = 2; // X
        a[i][1] = 3; // Y
        a[i][2] = 6; // Z
    }
    
    vector<double> c(n, 0.0);


    int c1 = n / count;
    int c2 = c1 + (n % count);
    vector<thread> t(count);
    for (int i = 0; i < count; i++) {
        if (i < count - 1) {
            t[i] = thread(f, ref(c), i, ref(a), c1);
        }
        else {
            t[i] = thread(f1, ref(c), i, ref(a), c2);
        }
    }

    for (int i = 0; i < count; i++) {
        t[i].join(); 
    }

    for (int i = 0; i < c.size(); i++) {
        cout << c[i] << " ";
    }
    cout << endl;

    return 0;
}
