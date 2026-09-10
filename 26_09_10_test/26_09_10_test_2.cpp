#include <iostream>
#include <thread>
#include <vector>
#include <string>
using namespace std;

void threadFunc(int ind, string &text) {
    int n = text.size();
    int st = ((n * ind) / 4);
    int en = ((n * (ind+1)) / 4);

    for (int i = st; i < en; ++i) {
        if (97 <= text[i] && text[i] <= 122) {
            //cout << text[i] << ' ';
            text[i] = ((text[i] - 97 + 3) % 26 ) + 97;
            //cout << text[i] << '\n';
        }

        if (65 <= text[i] && text[i] <= 90) {
            text[i] = ((text[i] - 65 + 3) % 26 ) + 65;
        }
    }
}

int main () {
    /*for (int i = 97; i <= 122; ++i) {
        cout << (char)(i);
    }
    cout << (int)('A') << ' ' << (int)('Z') << "\n\n";*/
    string text = "Hello, World!";
    vector<thread> threads;

    for (int i = 0; i < 4; ++i)
        threads.push_back(thread(threadFunc, i, ref(text)));
    for (int i = 0; i < 4; ++i)
        threads[i].join();
    
    cout << text << '\n';

    return 0;
}