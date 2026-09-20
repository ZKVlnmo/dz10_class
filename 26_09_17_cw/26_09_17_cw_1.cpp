#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void threadFunc(int ind, int k, vector<bool> &otv) {
    int n = otv.size();

    int st = ((n * ind) / k);
    int en = ((n * (ind+1)) / k);
    string line;

    for (int i = st; i < en; ++i) {
        string fileInd = to_string(i+1);
        if (fileInd.size() == 1) fileInd = "00"+fileInd;
        if (fileInd.size() == 2) fileInd = "0"+fileInd;
        ifstream file("zip/document_"+fileInd+".txt");

        while(getline(file, line)) {
            //cout << line.find(search_str) << ' ' << (line.find(search_str) == string::npos) << '\n';
            if (line.find(" dead ") != string::npos) {
                cout << "document_"+fileInd+".txt" << '\n';
                otv[i] = true;
                break;
            }

            if (line.find(" dead,") != string::npos) {
                cout << "document_"+fileInd+".txt" << '\n';
                otv[i] = true;
                break;
            }
        }

        file.close();
    }
}

int main () {
    int k = 4;
    vector<thread> threads;
    vector<bool> otv(100, false);

    for (int i = 0; i < k; ++i)
        threads.push_back(thread(threadFunc, i, k, ref(otv)));
    for (int i = 0; i < k; ++i)
        threads[i].join();

    return 0;
}
