#include <vector>
#include <algorithm>
#include "conventional.h"
#define INT_MAX 2147483647

// Cocktail Shaker Sort
void cocktailShakerSort(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;
    int start = 0, end = n - 1;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

// Comb Sort
void combSort(std::vector<int>& arr) {
    int n = arr.size();
    float shrink = 1.3f;
    int gap = n;
    bool swapped = true;
    while (gap > 1 || swapped) {
        gap = static_cast<int>(gap / shrink);
        if (gap < 1) gap = 1;
        swapped = false;

        for (int i = 0; i < n - gap; ++i) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

// Tournament Sort
int buildTree(std::vector<int>& tree, const std::vector<int>& arr) {
    int n = arr.size();
    int offset = 1;
    while (offset < n) offset *= 2;
    tree.resize(2 * offset, INT_MAX);
    for (int i = 0; i < n; ++i) tree[offset + i] = arr[i];
    for (int i = offset - 1; i > 0; --i) tree[i] = std::min(tree[2 * i], tree[2 * i + 1]);
    return offset;
}
void updateTree(std::vector<int>& tree, int index, int offset) {
    tree[offset + index] = INT_MAX;
    int i = (offset + index) / 2;
    while (i > 0) {
        tree[i] = std::min(tree[2 * i], tree[2 * i + 1]);
        i /= 2;
    }
}
std::vector<int> tournamentSort(const std::vector<int>& arr) {
    std::vector<int> tree;
    int offset = buildTree(tree, arr);
    std::vector<int> result;
    for (int k = 0; k < arr.size(); ++k) {
        int winner = tree[1];
        result.push_back(winner);
        int i = 1;
        while (i < offset) {
            i *= 2;
            if (tree[i] != winner) ++i;
        }
        int index = i - offset;
        updateTree(tree, index, offset);
    }
    return result;
}

// Library Sort
std::vector<int> librarySort(std::vector<int> A) {
    int n = A.size();
    std::vector<int> S(2 * n, INT_MAX);
    int count = 0;
    auto insert = [&](int x) {
        int left = 0, right = 2 * n - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (S[mid] == INT_MAX || S[mid] > x) right = mid;
            else left = mid + 1;
        }
        while (S[left] != INT_MAX) ++left;
        S[left] = x;
        ++count;
    };
    for (int x : A) insert(x);
    std::vector<int> result;
    for (int x : S)
        if (x != INT_MAX)
            result.push_back(x);
    return result;
}

// Intro Sort
void introSort(std::vector<int>& arr, int left, int right, int depthLimit) {
    int size = right - left + 1;
    if (size < 16) {
        insertionSort(arr, left, right);
        return;
    }
    if (depthLimit == 0) {
        heapSort(arr, left, right);
        return;
    }

    int pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) ++i;
        while (arr[j] > pivot) --j;
        if (i <= j) std::swap(arr[i++], arr[j--]);
    }

    if (left < j) introSort(arr, left, j, depthLimit - 1);
    if (i < right) introSort(arr, i, right, depthLimit - 1);
}

// Tim Sort
const int RUN = 32;
void timSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, std::min(i + RUN - 1, n - 1));

    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min(left + size - 1, n - 1);
            int right = std::min(left + 2 * size - 1, n - 1);
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}