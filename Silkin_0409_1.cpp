#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void threadfunc(int thread_id, int total_threads, int n, int m, int k,
                const vector<vector<int>> &a, const vector<vector<int>> &b,
                vector<vector<int>> &c) {
  for (int i = thread_id; i < n; i += total_threads) {
    for (int j = 0; j < k; j++) {
      for (int l = 0; l < m; l++) {
        c[i][j] += a[i][l] * b[l][j];
      }
    }
  }
}

int main() {
  int n, m, k;
  if (!(cin >> n >> m >> k))
    return 0;

  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }

  vector<vector<int>> b(m, vector<int>(k, 0));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < k; j++) {
      cin >> b[i][j];
    }
  }

  int num_threads = (k < m ? k : m);
  if (num_threads < 1)
    num_threads = 1;

  vector<vector<int>> c(n, vector<int>(k, 0));
  vector<thread> t;
  for (int i = 0; i < num_threads; i++) {
    t.push_back(
        thread(threadfunc, i, num_threads, n, m, k, cref(a), cref(b), ref(c)));
  }

  for (int i = 0; i < num_threads; i++) {
    t[i].join();
  }

  cout << "\nРезультат:\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      cout << c[i][j] << " ";
    }
    cout << endl;
  }

  cout << endl;
  system("pause");
  return 0;
}
