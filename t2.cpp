#include <iostream>
#include <thread>
#include <vector>

using matrix = std::vector<std::vector<int>>;

void mul(int line, matrix& x, std::vector<int>& b, std::vector<int>& c) {
    int n = x.size();
    int m = x[0].size();

    int k = 0;

    for (int j = 0; j < m; j++) {
        k += x[line][j] * b[j];
    }

    c[line] = k;
}

int main() {
    int n,m;

    std::cin >> n >> m;

    matrix x(n, std::vector<int>(m, 0));
    std::vector<int> b(m);
    std::vector<int> c(n);


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> x[i][j];
        }
    }


    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::vector<std::thread> v;

    for (int i = 0; i < n; i++) {
        v.push_back(std::thread(mul, i, std::ref(x), std::ref(b), std::ref(c)));
    }

    for (auto& i : v) i.join();
    for (const auto& i : c) {
        std::cout << i << ' ';
    }
    return 0;
}