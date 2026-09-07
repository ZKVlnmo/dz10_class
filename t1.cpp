#include <iostream>
#include <thread>
#include <vector>
//удобно
using matrix = std::vector<std::vector<int>>;
//матрица вывести
void pmat(matrix m) {
    for (const auto& i : m) {
        for (const auto& j : i) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
}
//умножить матрица
void mul(int line, matrix& a, matrix& b, matrix& c) {
    int n = a.size();
    int m = a[0].size();
    int k = b[0].size();

    for (int i = 0; i < k; i++) {
        int k = 0;

        for (int j = 0; j < m; j++) {
            k += a[line][j] * b[j][i];
        }

        c[line][i] = k;
    }
}



int main() {
    int n,m,k;

    std::cin >> n >> m >> k;

    matrix a(n, std::vector<int>(m, 0));
    matrix b(m, std::vector<int>(k, 0));
    matrix c(n, std::vector<int>(k, 0));
//матрица зополнить

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
//матреца б зополнить
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            std::cin >> b[i][j];
        }
    }
//вектолр патоКОВ
    std::vector<std::thread> v;

    for (int i = 0; i < n; i++) {
        v.push_back(std::thread(mul, i, std::ref(a), std::ref(b), std::ref(c)));
    }

    for (auto& i : v) i.join();
//ЮРПМЫЩЯ
    pmat(c);

    return true;
}