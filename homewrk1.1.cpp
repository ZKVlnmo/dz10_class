#include <iostream>
#include <thread>
#include <vector>

void multiplyRows(std::vector<std::vector<int>>& a,
                  std::vector<std::vector<int>>& b,
                  std::vector<std::vector<int>>& c,
                  int start, int end) {

    int colsA = a[0].size();
    int colsB = b[0].size();
    
    for (int i = start; i < end; i++) {
        for (int j = 0; j < colsB; j++) {
            int sum = 0;
            for (int k = 0; k < colsA; k++) {
                sum += a[i][k] * b[k][j];
            }

            c[i][j] = sum;
        }
    }
}

void parallelMatrixMultiply(std::vector<std::vector<int>>& a,
                            std::vector<std::vector<int>>& b,
                            std::vector<std::vector<int>>& c,
                            int threads) {

    int rows = a.size();
    int rowsPerThread = rows / threads;
    std::vector<std::thread> threadVec;
    
    for (int i = 0; i < threads; i++) {
        int start = i * rowsPerThread;
        int end = start + rowsPerThread;
        
        if (i == threads - 1) {
            end = rows;
        }
        
        threadVec.push_back(std::thread(multiplyRows, std::ref(a), std::ref(b),
                                   std::ref(c), start, end));
    }
    
    for (int i = 0; i < threadVec.size(); i++) {
        threadVec[i].join();
    }
}


int main() {
    std::vector<std::vector<int>> a = {{1, 2},
                                       {3, 4}};
    std::vector<std::vector<int>> b = {{5, 6},
                                       {7, 8}};
    std::vector<std::vector<int>> c = {{0, 0},
                                       {0, 0}};
    
    parallelMatrixMultiply(a, b, c, 2);
    
    for (auto& row : c) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}