#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

void f(vector<vector<int>>& c, int thread_id, vector<vector<int>> &a, vector<vector<int>> &core, int c1) {
    int start_row = 1 + thread_id * c1;
    int end_row = start_row + c1;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 1; j < a[0].size() - 1; j++) {
            int sum = 0;
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    sum += a[i + ki][j + kj] * core[ki + 1][kj + 1];
                }
            }
            c[i][j] = sum;
        }
    }
}

void f1(vector<vector<int>>& c, int thread_id, vector<vector<int>> &a, vector<vector<int>> &core, int c2) {
    int end_row = a.size() - 1;
    int start_row = end_row - c2; 
    for (int i = start_row; i < end_row; i++) {
        for (int j = 1; j < a[0].size() - 1; j++) {
            int sum = 0;
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    sum += a[i + ki][j + kj] * core[ki + 1][kj + 1];
                }
            }
            c[i][j] = sum;
        }
    }
}

int main() {
    int n;
    int m;
    int count;
    cout << "Write n";
    cin >> n;
    cout << "Write m";
    cin >> m;
    cout << "Write count of threads: ";
    cin >> count;

    vector<vector<int>> a(n, vector<int>(m, 2));
    vector<vector<int>> core = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    vector<vector<int>> c(n, vector<int>(m, 0));

    int inter_rows = n - 2;

    int c1 = inter_rows / count;
    int c2 = inter_rows - c1 * (count - 1);
    
    vector<thread> t(count);
    for (int i = 0; i < count; i++) {
        if (i < count - 1) {
            t[i] = thread(f, ref(c), i, ref(a), ref(core), c1);
        }
        else {
            t[i] = thread(f1, ref(c), i, ref(a), ref(core), c2);
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
