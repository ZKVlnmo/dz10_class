#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

const int N = 1000;

using Matrix = vector<vector<int>>;

Matrix generateMatrix(mt19937& gen)
{
    uniform_int_distribution<int> dist(0, 9);
    Matrix matrix(N, vector<int>(N));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = dist(gen);

    return matrix;
}

// Готовое однопоточное умножение
Matrix multiplyOneThread(const Matrix& A, const Matrix& B)
{
    Matrix C(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

// TODO: реализовать вычисление строк [startRow; endRow)
void multiplyPart(
    const Matrix& A,
    const Matrix& B,
    Matrix& C,
    int startRow,
    int endRow)
{
    // TODOint n = a.size();
    int n = A.size(), m = A[0].size(), k = B[0].size();

    for (int line = startRow; line < endRow; ++line) {
        for (int cell = 0; cell < k; ++cell) {
            int sam = 0;

            for (int t = 0; t < m; ++t)
                sam += A[line][t] * B[t][cell];
            
            //cout << sam << ' ';
            C[line][cell] = sam;
        }
    }
    //cout << '\n';
}

// TODO: реализовать многопоточное умножение
Matrix multiplyParallel(
    const Matrix& A,
    const Matrix& B,
    int threadCount)
{
    Matrix C(N, vector<int>(N, 0));
    vector<thread> threads;

    // TODO:
    // 1. Разделить строки матрицы между потоками
    // 2. Создать потоки
    // 3. В каждом вызвать multiplyPart(...)
    // 4. Выполнить join() для всех потоков

    for (int ind = 0; ind < threadCount; ++ind) {
        int st = ((N * ind) / threadCount);
        int en = ((N * (ind+1)) / threadCount);
        threads.push_back(thread(multiplyPart, ref(A), ref(B), ref(C), st, en));
    }
    for (int ind = 0; ind < threadCount; ++ind) {
        threads[ind].join();
    }

    return C;
}

int main()
{
    mt19937 gen(42);

    cout << "Генерация матриц...\n";

    Matrix A = generateMatrix(gen);
    Matrix B = generateMatrix(gen);

    auto start1 = chrono::steady_clock::now();
    Matrix C1 = multiplyOneThread(A, B);
    auto end1 = chrono::steady_clock::now();

    double time1 =
        chrono::duration<double>(end1 - start1).count();

    cout << "1 поток: " << time1 << " сек.\n";

    for (int threadCount = 2; threadCount <= 20; ++threadCount) {
        //int threadCount = 4;

        auto start2 = chrono::steady_clock::now();
        Matrix C2 = multiplyParallel(A, B, threadCount);
        auto end2 = chrono::steady_clock::now();

        double time2 =
            chrono::duration<double>(end2 - start2).count();

        cout << threadCount << " потоков: "
            << time2 << " сек. Ускорение: "
            << time1 / time2
            << " раз\n";

        if (C1 != C2)
            cout << "ОШИБКА: матрицы различаются\n";
    }

    return 0;
}
