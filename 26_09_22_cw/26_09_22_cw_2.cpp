#include <iostream>
#include <vector>
#include <future>
//#include <barrier>
#include <fstream>
using namespace std;

//barrier a(3);

unsigned long long asyncFunc(int ind, int k) {
    unsigned long long otv = 0;
    int st = ((10 * ind) / k);
    int en = ((10 * (ind+1)) / k);

    for (int fileNumber = st; fileNumber < en; ++fileNumber) {
        string fileInd = to_string(ind+1);
        if (fileInd.size() == 1) fileInd = "0"+fileInd;
        fstream file("zip/file_"+fileInd+".txt");
        vector<unsigned long long> massiv(0);
        string reader;

        while (file >> reader) {
            if (reader != ".") {fstream file("zip/file_"+fileInd+".txt");
                unsigned long long val = stoi(reader);
                massiv.push_back(val);
            }
            else {
                for (int a = 4; a < massiv.size(); ++a) {
                    for (int b = 3; b < a; ++b) {
                        for (int c = 2; c < b; ++c) {
                            for (int d = 1; d < c; ++d) {
                                for (int e = 0; e < d; ++e) {

if ((massiv[a] + massiv[b] + massiv[c] + massiv[d] + massiv[e]) % 10 == 1) otv ++;

                                }
                            }
                        }
                    }
                }

                massiv = vector<unsigned long long>(0);
            }
        }
        file.close();
    }
    //a.arrive_and_wait();
    return otv;
}

int main() {
    int k = 3;
    unsigned long long otv = 0;
    vector<future<unsigned long long>> res(k);

    for (int i = 0; i < k; ++i)
        res[i] = async(launch::async, asyncFunc, i, k);
    for (int i = 0; i < k; ++i)
        otv += res[i].get();

    cout << otv << '\n';
    return 0;
}