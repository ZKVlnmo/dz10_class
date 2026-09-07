#include <iostream>
#include <vector>
#include <cmath>
#include <thread>

struct vec3 {
    int x, y, z;
};

void calcDist(const std::vector<vec3>& points, std::vector<float>& dist, int start, int end) {
    for (int i = start; i < end; i++) {
        dist[i] = std::sqrt(points[i].x * points[i].x + points[i].y * points[i].y + points[i].z * points[i].z);
    }
}

int main() {
    int n;
    int k;

    std::cout << "入れる n k" << std::endl;

    std::cin >> n >> k;

    std::vector<vec3> points(n);
    std::vector<float> dist(n);

    std::cout << "挿入ポイント" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cin >> points[i].x;
        std::cin >> points[i].y;
        std::cin >> points[i].z;
    }

    std::vector<std::thread> threads;

    int chunk = n / k;
    int rem = n % k;

    int start = 0;
    for (int i = 0; i < k; i++) {
        int current = chunk + (int)(i < rem);
        int end = start + current;

        if (start < end) {
            threads.push_back(std::thread(calcDist, std::ref(points), std::ref(dist), start, end));
        }

        start = end;
    }

    for (auto& i : threads) i.join();

    for (int i = 0; i < n; i++) {
        std::cout << dist[i] << ' ';
    }
    std::cout << std::endl;
}
