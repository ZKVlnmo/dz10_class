#include <iostream>
#include <vector>
#include <thread>
using namespace std;
void calc(int** a, int** b, int** c, int start, int end, int m, int k) 
{
    for (int i = start; i < end; i++) 
    {
        for (int j = 0; j < k; j++) 
        {
            c[i][j] = 0;
            for (int t = 0; t < m; t++) 
            {
                c[i][j] += a[i][t] * b[t][j];
            }
        }
    }
}
int main() 
{
    int n = 6;
    int m = 4;
    int k = 5;
    int** a = new int*[n];
    for (int i = 0; i < n; i++) 
    {
        a[i] = new int[m];
    }

    int** b = new int*[m];
    for (int i = 0; i < m; i++) 
    {
        b[i] = new int[k];
    }

    int** c = new int*[n];
    for (int i = 0; i < n; i++) 
    {
        c[i] = new int[k];
    }
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            a[i][j] = 1;
        }
    }
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < k; j++) 
        {
            b[i][j] = 2;
        }
    }

    int count = 2;
    vector<thread> ths;
    int step = n / count;

    for (int i = 0; i < count; i++) 
    {
        int start = i * step;
        int end = (i == count - 1) ? n : start + step;
        ths.emplace_back(calc, a, b, c, start, end, m, k);
    }
    for (auto& t : ths) 
    {
        t.join();
    }
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < k; j++) 
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++) 
    {
        delete[] a[i];
    }
    delete[] a;
    for (int i = 0; i < m; i++) 
    {
        delete[] b[i];
    }
    delete[] b;
    for (int i = 0; i < n; i++) 
    {
        delete[] c[i];
    }
    delete[] c;
}