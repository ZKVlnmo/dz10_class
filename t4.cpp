#include <iostream>
#include <vector>
#include <cmath>
#include <thread>

struct vec3 {
    int x, y, z;
};

void cd(const std::vector<vec3>& pts, std::vector<float>& dist, int start, int end) {
    for (int i = start; i < end; i++) {
        dist[i] = std::sqrt(pts[i].x * pts[i].x + pts[i].y * pts[i].y + pts[i].z * pts[i].z);
    }
}

int main() {
    int n, k;

    std::cin >> n >> k;

    std::vector<vec3> pts(n);
    std::vector<float> dist(n);

    for (int i = 0; i < n; i++) {
        std::cin >> pts[i].x;
        std::cin >> pts[i].y;
        std::cin >> pts[i].z;
    }

    int ck = n / k;
    int rem = n % k;

    std::vector<std::thread> thr;

    int start = 0;
    for (int i = 0; i < k; i++) {
        int crr = ck + (int)(i < rem);
        int end = start + crr;

        if (start < end) {
            thr.push_back(std::thread(cd, std::ref(pts), std::ref(dist), start, end));
        }

        start = end;
    }

    for (auto& i : thr) i.join();

    for (int i = 0; i < n; i++) {
        std::cout << dist[i] << ' ';
    }
    std::cout << std::endl;
}