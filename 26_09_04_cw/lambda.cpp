#include<iostream>
//#include<unistd.h>
//#include<lock>
#include<functional>
#include<vector>
using namespace std;

int oper(int a, int b, function<int(int, int)> func) {
    return func(a,b);
}

int main () {
    auto maxa = [](int a, int b){
        if (a > b) return a;
        return b;
    };
    cout << maxa(52, 67) << '\n';

    int n = 12;
    auto multi5 = [&n]() { n *= 5; };
    multi5();
    cout << n << '\n';

    cout << oper(52, 67, [](int a, int b){ return a+b; });

    return 0;
}