#include <algorithm>
#include <climits>
#include "type.h"

// Bubble Sort
void bubbleSort(TaggedValue* A, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (A[j].value > A[j + 1].value) {
                std::swap(A[j], A[j + 1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(TaggedValue* A, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int jMin = i;
        for (int j = i + 1; j < n; ++j) {
            if (A[j].value < A[jMin].value) {
                jMin = j;
            }
        }
        if (jMin != i) {
            std::swap(A[i], A[jMin]);
        }
    }
}

// Insertion Sort
void insertionSort(TaggedValue* A, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int j = i;
        while (j > left && A[j - 1].value > A[j].value) {
            std::swap(A[j], A[j - 1]);
            --j;
        }
    }
}
void insertionSort(TaggedValue* A, int n) {
    insertionSort(A, 0, n - 1);
}

// Quick Sort
int partition(TaggedValue* A, int low, int high) {
    TaggedValue pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (A[j].value <= pivot.value) {
            ++i;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[high]);
    return i + 1;
}
void quickSort(TaggedValue* A, int low, int high) {
    if (low < high) {
        int p = partition(A, low, high);
        quickSort(A, low, p - 1);
        quickSort(A, p + 1, high);
    }
}
void quickSort(TaggedValue* A, int n) {
    quickSort(A, 0, n - 1);
}

// Quick Sort 2, with median-of-three pivot selection
int medianOfThree(TaggedValue* A, int low, int high) {
    int mid = low + (high - low) / 2;
    if (A[low].value > A[mid].value) std::swap(A[low], A[mid]);
    if (A[low].value > A[high].value) std::swap(A[low], A[high]);
    if (A[mid].value > A[high].value) std::swap(A[mid], A[high]);
    return mid;
}
int partitionMedianOfThree(TaggedValue* A, int low, int high) {
    int pivotIndex = medianOfThree(A, low, high);
    std::swap(A[pivotIndex], A[high]);
    TaggedValue pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (A[j].value <= pivot.value) {
            ++i;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[high]);
    return i + 1;
}
void quickSort2(TaggedValue* A, int low, int high) {
    if (low < high) {
        int p = partitionMedianOfThree(A, low, high);
        quickSort2(A, low, p - 1);
        quickSort2(A, p + 1, high);
    }
}
void quickSort2(TaggedValue* A, int n) {
    quickSort2(A, 0, n - 1);
}

// Heap Sort
void heapify(TaggedValue* A, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left].value > A[largest].value) {
        largest = left;
    }
    if (right < n && A[right].value > A[largest].value) {
        largest = right;
    }
    if (largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}
void heapSort(TaggedValue* A, int low, int high) {
    int n = high - low + 1;
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(A + low, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        std::swap(A[low], A[low + i]);
        heapify(A + low, i, 0);
    }
}
void heapSort(TaggedValue* A, int n) {
    heapSort(A, 0, n - 1);
}

// Merge Sort
void merge(TaggedValue* A, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    TaggedValue* L = new TaggedValue[n1 + 1];
    TaggedValue* R = new TaggedValue[n2 + 1];
    for (int i = 0; i < n1; ++i) L[i] = A[left + i];
    for (int j = 0; j < n2; ++j) R[j] = A[mid + 1 + j];
    L[n1] = TaggedValue{INT_MAX, -1};
    R[n2] = TaggedValue{INT_MAX, -1};

    int i = 0, j = 0;
    for (int k = left; k <= right; ++k) {
        if (L[i].value <= R[j].value)
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }
    delete[] L;
    delete[] R;
}
void mergeSort(TaggedValue* A, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}
void mergeSort(TaggedValue* A, int n) {
    mergeSort(A, 0, n - 1);
}

