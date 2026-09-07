#include <iostream>
#include <thread>
#include <vector>

using mtrx = std::vector<std::vector<int>>;

void mul(int ln, mtrx& a, std::vector<int>& b, std::vector<int>& c) {
    int n = a.size();
    int m = a[0].size();

    int 和 = 0;

    for (int j = 0; j < m; j++) {
        和 += a[ln][j] * b[j];
    }

    c[ln] = 和;
}

int main() {
    int n = 4;
    int m = 4;

    std::cout << "入れる n m" << std::endl;

    std::cin >> n >> m;

    mtrx a(n, std::vector<int>(m, 0));
    std::vector<int> b(m);
    std::vector<int> c(n);

    std::cout << "マットリクスA:" << std::endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    std::cout << "ベクターX:" << std::endl;

    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::vector<std::thread> v;

    for (int i = 0; i < n; i++) {
        v.push_back(std::thread(mul, i, std::ref(a), std::ref(b), std::ref(c)));
    }

    for (auto& i : v) i.join();

    std::cout << "結果: ";
    for (const auto& i : c) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    return 0;
}

