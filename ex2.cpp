#include <iostream>
#include <vector>
#include <thread>
using namespace std;
void calc(int** a, int* x, int* y, int start, int end, int m) 
{
    for (int i = start; i < end; i++) 
    {
        y[i] = 0;
        for (int j = 0; j < m; j++) 
        {
            y[i] += a[i][j] * x[j];
        }
    }
}
int main() 
{
    int n = 6;
    int m = 4;
    int** a = new int*[n];
    for (int i = 0; i < n; i++) 
    {
        a[i] = new int[m];
    }
    int* x = new int[m];
    int* y = new int[n];
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            a[i][j] = 2;
        }
    }
    for (int j = 0; j < m; j++) 
    {
        x[j] = 3;
    }
    int count = 2;
    vector<thread> ths;
    int step = n / count;
    for (int i = 0; i < count; i++) 
    {
        int start = i * step;
        int end = (i == count - 1) ? n : start + step;
        ths.emplace_back(calc, a, x, y, start, end, m);
    }
    for (auto& t : ths) 
    {
        t.join();
    }
    for (int i = 0; i < n; i++) 
    {
        cout << y[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) 
    {
        delete[] a[i];
    }
    delete[] a;
    delete[] x;
    delete[] y;
}