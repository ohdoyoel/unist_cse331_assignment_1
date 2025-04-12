#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdint>
#include <vector>
#include <numeric>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <windows.h>
#include <psapi.h>
#include <fstream>
#include <sstream>
#include <string>
#include <dirent.h>
#include <map>
#include "generateTestCase.h"
#include "../src/conventional.h"
#include "../src/contemporary.h"

uint64_t getMemoryUsageBytes() {
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        return static_cast<uint64_t>(memInfo.WorkingSetSize);
    }
    return 0;
}

bool isCorrect(TaggedValue* arr, int n) {
    for (int i = 1; i < n; ++i)
        if (arr[i - 1].value > arr[i].value) return false;
    return true;
}

bool isStable(TaggedValue* arr, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i].value == arr[j].value && arr[i].originalIndex > arr[j].originalIndex) {
                return false;
            }
        }
    }
    return true;
}

using SortFunction = void(*)(TaggedValue*, int);

struct Metrics {
    double time;
    uint64_t memory;
    bool correct;
    bool stable;
};

Metrics runSingleTrial(SortFunction sortFn, int* original, int n) {
    TaggedValue* arr = new TaggedValue[n];
    for (int i = 0; i < n; ++i) {
        arr[i].value = original[i];
        arr[i].originalIndex = i;
    }

    uint64_t memBefore = getMemoryUsageBytes();
    auto start = std::chrono::high_resolution_clock::now();
    sortFn(arr, n);
    auto end = std::chrono::high_resolution_clock::now();
    uint64_t memAfter = getMemoryUsageBytes();

    double elapsed = std::chrono::duration<double>(end - start).count();
    uint64_t memUsed = memAfter >= memBefore ? (memAfter - memBefore) : 0;

    bool correct = isCorrect(arr, n);
    bool stable = isStable(arr, n);

    delete[] arr;
    return {elapsed, memUsed, correct, stable};
}

Metrics averageMetrics(const std::vector<Metrics>& trialResults) {
    double totalTime = 0;
    double totalMemory = 0;
    bool allCorrect = true;
    bool allStable = true;

    for (const auto& m : trialResults) {
        totalTime += m.time;
        totalMemory += m.memory;
        allCorrect &= m.correct;
        allStable &= m.stable;
    }

    int count = trialResults.size();
    return {totalTime / count, static_cast<uint64_t>(totalMemory / count), allCorrect, allStable};
}

bool endsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int* loadArrayFromFile(const std::string& filepath, int& sizeOut) {
    std::ifstream in(filepath.c_str());
    std::vector<int> data;
    int value;
    while (in >> value)
        data.push_back(value);
    sizeOut = data.size();
    int* arr = new int[sizeOut];
    std::copy(data.begin(), data.end(), arr);
    return arr;
}

std::vector<std::string> getAllTestFiles(const std::string& folder) {
    std::vector<std::string> files;
    DIR* dir = opendir(folder.c_str());
    if (!dir) {
        std::cerr << "Failed to open directory: " << folder << "\n";
        std::exit(1);
    }
    dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string name = entry->d_name;
        if (endsWith(name, ".txt")) {
            files.push_back(folder + "/" + name);
        }
    }
    closedir(dir);
    return files;
}

struct TestFileInfo {
    std::string fullPath;
    std::string type;
    int size;
    int trial;
};

std::vector<TestFileInfo> parseAndSortTestFiles(const std::vector<std::string>& filepaths) {
    std::vector<TestFileInfo> files;
    for (const auto& path : filepaths) {
        std::string filename = path.substr(path.find_last_of("/\\") + 1);
        size_t p1 = filename.find('_');
        size_t p2 = filename.find('_', p1 + 1);
        size_t p3 = filename.find('.', p2);
        if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos)
            continue;
        std::string type = filename.substr(0, p1);
        int size = std::stoi(filename.substr(p1 + 1, p2 - p1 - 1));
        int trial = std::stoi(filename.substr(p2 + 1, p3 - p2 - 1));
        files.push_back({path, type, size, trial});
    }
    std::sort(files.begin(), files.end(), [](const TestFileInfo& a, const TestFileInfo& b) {
        if (a.size != b.size) return a.size < b.size;
        if (a.type != b.type) return a.type < b.type;
        return a.trial < b.trial;
    });
    return files;
}

int main() {
    const int trials = 10;
    // generateAllTestcases({1000, 10000, 100000, 1000000}, trials);

    const std::string testFolder = "test/testCase";

    struct Algo {
        const char* name;
        SortFunction fn;
    } algorithms[] = {
        // {"Bubble", bubbleSort},
        // {"Selection", selectionSort},
        // {"Insertion", insertionSort},
        // {"Quick", quickSort},
        // {"Quick2", quickSort2},
        {"Heap", heapSort},
        {"Merge", mergeSort},
        // {"Cocktail", cocktailShakerSort},
        // {"Comb", combSort},
        {"Tournament", tournamentSort},
        // {"Library", librarySort},
        {"Intro", introSort},
        {"Tim", timSort}
    }; // can use comments for experimental restrictions

    std::vector<std::string> rawFiles = getAllTestFiles(testFolder);
    std::vector<TestFileInfo> testFiles = parseAndSortTestFiles(rawFiles);

    std::pair<int, std::string> lastGroupKey = {-1, ""};

    for (auto& algo : algorithms) {
        std::pair<int, std::string> lastGroupKey = {-1, ""};
        std::vector<Metrics> results;

        std::cout << "\n" << algo.name << " Sort Progress:\n";

        for (const auto& file : testFiles) {
            if (file.size != 1000000) continue;
            // if (file.type != "random") continue;
            // also can use if statements for experimental restrictions

            std::pair<int, std::string> currentGroupKey = {file.size, file.type};

            if (currentGroupKey != lastGroupKey && !results.empty()) {
                Metrics avg = averageMetrics(results);
                std::cout << std::setw(10) << algo.name << " | "
                          << std::setw(10) << std::fixed << std::setprecision(10) << avg.time << " sec | "
                          << std::setw(10) << avg.memory << " B | "
                          << (avg.correct ? "Correct" : "Wrong") << " | "
                          << (avg.stable ? "Stable" : "Unstable") << "\n";
                results.clear();
            }

            if (currentGroupKey != lastGroupKey) {
                std::cout << "\n--- Data Size: " << file.size << " | Type: " << file.type << " ---\n";
                lastGroupKey = currentGroupKey;
            }

            int loadedSize = 0;
            int* original = loadArrayFromFile(file.fullPath, loadedSize);
            if (loadedSize != file.size) {
                std::cerr << "Size mismatch in " << file.fullPath << "\n";
                delete[] original;
                continue;
            }

            std::cout << "  Trial " << (file.trial + 1) << "/" << trials << "..." << std::flush;
            Metrics m = runSingleTrial(algo.fn, original, file.size);
            std::cout << " done in " << std::fixed << std::setprecision(10) << m.time << "s, "
                      << std::fixed << std::setprecision(10) << m.memory << " B used\n";
            results.push_back(m);
            delete[] original;
        }

        if (!results.empty()) {
            Metrics avg = averageMetrics(results);
            std::cout << std::setw(10) << algo.name << " | "
                      << std::setw(10) << std::fixed << std::setprecision(6) << avg.time << " sec | "
                      << std::setw(8) << avg.memory << " B | "
                      << (avg.correct ? "Correct" : "Wrong") << " | "
                      << (avg.stable ? "Stable" : "Unstable") << "\n";
        }
    }

    return 0;
}
