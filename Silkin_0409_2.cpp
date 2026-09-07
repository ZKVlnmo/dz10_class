#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void threadfunc(int n, int m, int k, int l, vector<vector<int>> a,
                vector<int> x, vector<vector<int>> c) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < l; j++) {
      for (int k = 0; k < m; k++) {
        c[i][j] += a[i][k] * x[k];
      }
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }

  vector<int> x(m);
  for (int i = 0; i < m; i++) {
    cin >> x[i];
  }

  int k, l;
  cin >> k >> l;
  vector<vector<int>> b(k, vector<int>(l));
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < l; j++) {
      cin >> b[i][j];
    }
  }

  vector<vector<int>> c;

  vector<thread> threads;
  for (int i = 0; i < m; i++) {
    threads.push_back(thread(threadfunc, n, m, k, l, a, x, c));
  }

  for (int i = 0; i < m; i++) {
    threads[i].join();
  }

  cout << "\nРезультат:\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < l; j++) {
      cout << c[i][j] << " ";
    }
    cout << endl;
  }

  system("pause");
  return 0;
}