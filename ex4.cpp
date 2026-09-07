#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
using namespace std;
void calc(double* x, double* y, double* z, double* d, int start, int end) 
{
    for (int i = start; i < end; i++) 
    {
        d[i] = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
    }
}
int main() 
{
    int n = 6;
    double* x = new double[n];
    double* y = new double[n];
    double* z = new double[n];
    double* d = new double[n];
    for (int i = 0; i < n; i++) 
    {
        x[i] = i + 1;
        y[i] = i + 2;
        z[i] = i + 3;
    }

    int count = 2;
    vector<thread> ths;
    int step = n / count;
    for (int i = 0; i < count; i++) 
    {
        int start = i * step;
        int end = (i == count - 1) ? n : start + step;
        ths.emplace_back(calc, x, y, z, d, start, end);
    }
    for (auto& t : ths) 
    {
        t.join();
    }
    for (int i = 0; i < n; i++) 
    {
        cout << d[i] << " ";
    }
    cout << endl;
    delete[] x;
    delete[] y;
    delete[] z;
    delete[] d;
}