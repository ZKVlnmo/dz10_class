#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

void f(vector<vector<int>>& c, int thread_id, vector<vector<int>> &a, vector<vector<int>> &b, int c1) {
    int c1_local = a.size() / (thread_id + 1);
    int start_row = thread_id * c1_local;
    int end_row = a.size();

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void f1(vector<vector<int>>& c, int thread_id, vector<vector<int>> &a, vector<vector<int>> &b, int c2) {
    int start_row = a.size() - c2; 
    int end_row = a.size();

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
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

    vector<vector<int>> a(n, vector<int>(m, 2)); 
    vector<vector<int>> b(m, vector<int>(k, 3));
    vector<vector<int>> c(n, vector<int>(k, 0));


    int c1 = n / count;
    int c2 = c1 + (n % count);
    vector<thread> t(count);
    for (int i = 0; i < count; i++) {
        if (i < count - 1) {
            t[i] = thread(f, ref(c), i, ref(a), ref(b), c1);
        }
        else {
            t[i] = thread(f1, ref(c), i, ref(a), ref(b), c2);
        }
    }

    for (int i = 0; i < count; i++) {
        t[i].join(); 
    }

    for (int i = 0; i < c.size(); i++) {
        for (int j = 0; j < c[0].size(); j++) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
