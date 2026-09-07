#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

struct Point {
  double x;
  double y;
  double z;
};

void threadfunc(int thread_id, int total_threads, int n,
                const vector<Point> &points, vector<double> &d) {
  for (int i = thread_id; i < n; i += total_threads) {
    d[i] = sqrt(points[i].x * points[i].x + points[i].y * points[i].y +
                points[i].z * points[i].z);
  }
}

int main() {
  setlocale(LC_ALL, "Russian");
  int n, k;
  if (!(cin >> n >> k) || n <= 0 || k <= 0) {
    return 0;
  }
  vector<Point> points(n);
  for (int i = 0; i < n; i++) {
    cin >> points[i].x >> points[i].y >> points[i].z;
  }

  int num_threads = (k < n ? k : n);
  if (num_threads < 1) {
    num_threads = 1;
  }

  vector<double> d(n, 0.0);

  vector<thread> t;
  t.reserve(num_threads);
  for (int i = 0; i < num_threads; i++) {
    t.push_back(thread(threadfunc, i, num_threads, n, cref(points), ref(d)));
  }

  for (int i = 0; i < num_threads; i++) {
    t[i].join();
  }
  cout << "\nResult:\n";
  for (int i = 0; i < n; i++) {
    cout << "d[" << i << "] = " << d[i] << "\n";
  }

  cout << endl;
  system("pause");
  return 0;
}
