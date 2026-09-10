#include <iostream>
#include <thread>
#include <vector>
#include <string>
using namespace std;

void threadFunc(int ind, string &text, vector<int> &numbers, vector<int> &spaces) {
    int n = text.size();
    int st = ((n * ind) / 4);
    int en = ((n * (ind+1)) / 4);

    for (int i = st; i < en; ++i) {
        if (text[i] == ' ') spaces[ind]++;
        else if (isdigit(text[i])) numbers[ind]++; 
    }
}

int main () {
    string text = "Hello world 2026! Parallel programming is fun.";
    vector<thread> threads;
    vector<int> numbers(4, 0), spaces(4, 0);

    for (int i = 0; i < 4; ++i)
        threads.push_back(thread(threadFunc, i, ref(text), ref(numbers), ref(spaces)));
    for (int i = 0; i < 4; ++i)
        threads[i].join();

    int number=0, space=0;

    for (int i = 0; i < 4; ++i) {
        number += numbers[i];
        space += spaces[i];
    }

    cout << number << ' ' << space << '\n';

    return 0;
}