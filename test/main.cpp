#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>   // rand()
#include <ctime>     // time()
#include "../src/conventional.h"
#include "../src/contemporary.h"

int main() {
    const int SIZE = 10'000'000;
    std::cout << "Data size: " << SIZE << "\n";

    std::vector<int> data(SIZE);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < SIZE; ++i) {
        data[i] = std::rand();
    }

    auto start = std::chrono::high_resolution_clock::now();
    timSort(data);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";

    for (int i = 0; i < 10; ++i) {
        std::cout << data[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}
