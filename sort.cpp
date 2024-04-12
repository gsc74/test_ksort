#include <iostream>
#include <vector>
#include "ksort.h"
#include <algorithm>
#include <cmath>
#include <execution>
#include <chrono>

typedef struct { uint64_t x, y; } mm128_t;

#define sort_key_128x(a) ((a).x)
KRADIX_SORT_INIT(128x, mm128_t, sort_key_128x, 8) 

int main() {
    std::vector<mm128_t> a;
    int32_t n = pow(10, 3);

    // for all i and j <= 10 fill a with random values
    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j < n; ++j) {
            mm128_t x = {i, j};
            a.push_back(x);
        }
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<mm128_t> c = a;
    radix_sort_128x(a.data(), a.data() + a.size());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken for radix sort: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    auto start2 = std::chrono::high_resolution_clock::now();
    std::stable_sort(std::execution::par_unseq, c.begin(), c.end(), [](const mm128_t& a, const mm128_t& b) {
        return a.x < b.x;
    });
    auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken for std::stable_sort: " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << " ms\n";

    // verify that the sort is correct
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].x != c[i].x || a[i].y != c[i].y) 
        {
            std::cerr << "Error: a[" << i << "] = {" << a[i].x << ", " << a[i].y << "} != c[" << i << "] = {" << c[i].x << ", " << c[i].y << "}\n";
            return 1;
        }
    }

    return 0;
}