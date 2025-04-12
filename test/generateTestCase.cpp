#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

void makeDirectory(const std::string& path) {
#ifdef _WIN32
    _mkdir("test");
    _mkdir(path.c_str());
#else
    mkdir("test", 0755);
    mkdir(path.c_str(), 0755);
#endif
}

void generateRandomArray(int* arr, int n) {
    for (int i = 0; i < n; ++i)
        arr[i] = rand();
}

void generateSortedArray(int* arr, int n) {
    if (n <= 0) return;
    arr[0] = rand() % 10;
    for (int i = 1; i < n; ++i)
        arr[i] = arr[i - 1] + rand() % 10;
}

void generateReverseSortedArray(int* arr, int n) {
    if (n <= 0) return;
    arr[n - 1] = rand() % 10;
    for (int i = n - 2; i >= 0; --i)
        arr[i] = arr[i + 1] + rand() % 10;
}

void generatePartiallySortedArray(int* arr, int n) {
    for (int i = 0; i < n; ++i)
        arr[i] = i;
    for (int i = 0; i < n / 3; ++i) {
        int a = rand() % n;
        int b = rand() % n;
        std::swap(arr[a], arr[b]);
    }
}

void generateArrayByType(int* arr, int n, const std::string& type) {
    if (type == "random") generateRandomArray(arr, n);
    else if (type == "sorted") generateSortedArray(arr, n);
    else if (type == "reversed") generateReverseSortedArray(arr, n);
    else if (type == "partial") generatePartiallySortedArray(arr, n);
    else {
        std::cerr << "Unknown type: " << type << "\n";
        std::exit(1);
    }
}

void writeArrayToFile(int* arr, int n, const std::string& filename) {
    std::string folder = "test/testCase";
    makeDirectory(folder);

    std::string filepath = folder + "/" + filename;

    std::ofstream out(filepath.c_str());
    for (int i = 0; i < n; ++i) {
        out << arr[i];
        if (i != n - 1) out << ' ';
    }
    out << "\n";
    out.close();
}

void generateAllTestcases(const std::vector<int>& sizes, int trials) {
    std::vector<std::string> types = {
        "random", "sorted", "reversed", "partial"
    };

    for (int size : sizes) {
        int* arr = new int[size];

        for (int t = 0; t < trials; ++t) {
            for (size_t i = 0; i < types.size(); ++i) {
                const std::string& type = types[i];
                generateArrayByType(arr, size, type);
                std::string filename = type + "_" + std::to_string(size) + "_" + std::to_string(t) + ".txt";
                writeArrayToFile(arr, size, filename);
                std::cout << "Generated: " << filename << "\n";
            }
        }

        delete[] arr;
    }
}