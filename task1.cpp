#include <iostream>
#include <thread>
#include <vector>

using mtrx = std::vector<std::vector<int>>;

void mul(int ln, mtrx& a, mtrx& b, mtrx& c) {
    int n = a.size();
    int m = a[0].size();
    int k = b[0].size();

    for (int i = 0; i < k; i++) {
        int 和 = 0;

        for (int j = 0; j < m; j++) {
            和 += a[ln][j] * b[j][i];
        }

        c[ln][i] = 和;
    }
}

void printMat(mtrx m) {
    for (const auto& i : m) {
        for (const auto& j : i) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    int n = 4;
    int m = 4;
    int k = 4;

    std::cout << "入れる n m k" << std::endl;

    std::cin >> n >> m >> k;

    mtrx a(n, std::vector<int>(m, 0));
    mtrx b(m, std::vector<int>(k, 0));
    mtrx c(n, std::vector<int>(k, 0));

    std::cout << "マットリクスA:" << std::endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    std::cout << "マットリクスB:" << std::endl;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            std::cin >> b[i][j];
        }
    }

    std::vector<std::thread> v;

    for (int i = 0; i < n; i++) {
        v.push_back(std::thread(mul, i, std::ref(a), std::ref(b), std::ref(c)));
    }

    for (auto& i : v) i.join();

    printMat(c);

    return 0;
}
