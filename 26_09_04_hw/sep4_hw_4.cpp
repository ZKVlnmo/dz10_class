#include<iostream>
#include<thread>
//#include<unistd.h>
//#include<lock>
#include<vector>
#include<math.h>
using namespace std;

struct Point {
    int x, y, z;

    Point(int _x,int _y, int _z) { x = _x; y = _y; z = _z; }
};

void threadFunc(int ind, vector<Point> &points, vector<double> &results, int k) {
    int n = points.size();//, k = results.size();

    int st = ((n * ind) / k);
    int en = ((n * (ind+1)) / k);

    for (int i = st; i < en; ++i) {
        results[i] = sqrt(points[i].x*points[i].x + points[i].y*points[i].y + points[i].z*points[i].z);
    }
}

int main () {
    vector<thread> threads;
    vector<Point> points = {Point(0, 0, 0), Point(1, 0, 0), Point(1, 1, 0), Point(1, 1, 1)};
    vector<double> results(points.size());
    int n = points.size();
    int k; cin >> k;

    for (int i = 0; i < k; ++i)
        threads.push_back(thread(threadFunc, i, ref(points), ref(results), k));
    for (int i = 0; i < k; ++i)
        threads[i].join();
    
    

    return 0;
}