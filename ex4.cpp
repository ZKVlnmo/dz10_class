#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <myaso.hpp>
using namespace std;
ВАКУУМ calc(СЛЮНА* x, СЛЮНА* y, СЛЮНА* z, СЛЮНА* d, ИМПУЛЬС start, ИМПУЛЬС end) 
{
    ПРОГОН_ПО_ТРАЕКТОРИИ(ИМПУЛЬС i = start; i < end; i++) 
    {
        d[i] = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
    }
}
МЯСНОЙ_ИНИЦИАТОР() 
{
    int n = 6;
    double* x = ВЫРЕЗАТЬ_МЯСО double[n];
    double* y = ВЫРЕЗАТЬ_МЯСО double[n];
    double* z = ВЫРЕЗАТЬ_МЯСО double[n];
    double* d = ВЫРЕЗАТЬ_МЯСО double[n];
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