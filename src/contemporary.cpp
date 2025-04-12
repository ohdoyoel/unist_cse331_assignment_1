#include <algorithm>
#include <climits>
#include <cmath>
#include <stdexcept>
// #include <vector>
#include <iostream>
#include <cstring>
#include "conventional.h"

// Cocktail Shaker Sort
void cocktailShakerSort(TaggedValue* A, int n) {
    int start = 0, end = n - 1;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (A[i].value > A[i + 1].value) {
                std::swap(A[i], A[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        --end;
        swapped = false;
        for (int i = end - 1; i >= start; --i) {
            if (A[i].value > A[i + 1].value) {
                std::swap(A[i], A[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

// Comb Sort
void combSort(TaggedValue* A, int n) {
    int gap = n;
    const double shrink = 1.3;
    bool swapped = true;
    while (gap > 1 || swapped) {
        gap = static_cast<int>(gap / shrink);
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i < n - gap; ++i) {
            if (A[i].value > A[i + gap].value) {
                std::swap(A[i], A[i + gap]);
                swapped = true;
            }
        }
    }
}

// Tournament Sort
void tournamentSort(TaggedValue* A, int n) {
    int m = 1;
    while (m < n) m *= 2;
    TaggedValue* T = new TaggedValue[2 * m - 1];
    for (int i = 0; i < n; ++i)
        T[m - 1 + i] = A[i];
    for (int i = m - 1 + n; i < 2 * m - 1; ++i)
        T[i].value = INT_MAX;
    for (int i = m - 2; i >= 0; --i)
        T[i] = (T[2 * i + 1].value <= T[2 * i + 2].value) ? T[2 * i + 1] : T[2 * i + 2];
    for (int k = 0; k < n; ++k) {
        A[k] = T[0];
        int i = m - 1;
        while (i < m - 1 + n && !(T[i].value == T[0].value && T[i].originalIndex == T[0].originalIndex))
            ++i;

        if (i >= m - 1 + n) {
            std::cerr << "[Error] Matching leaf not found for T[0]!\n";
            delete[] T;
            return;
        }
        
        T[i].value = INT_MAX;
        while (i > 0) {
            i = (i - 1) / 2;
            T[i] = (T[2 * i + 1].value <= T[2 * i + 2].value) ? T[2 * i + 1] : T[2 * i + 2];
        }
    }
    delete[] T;
}

// Library Sort
int findNear(TaggedValue* arr, bool* filled, int index, int start, int end) {
    if (filled[index]) return index;
    int left = index - 1, right = index + 1;
    while (left >= start || right <= end) {
        if (left >= start && filled[left]) return left;
        if (right <= end && filled[right]) return right;
        --left; ++right;
    }
    return -1;
}
int libinary(TaggedValue* arr, bool* filled, int len, int val) {
    int left = 0, right = len - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int found = findNear(arr, filled, mid, left, right);
        if (found == -1) break;
        if (val < arr[found].value) right = found - 1;
        else left = found + 1;
    }
    return (left + right) / 2;
}
int nearNull(bool* filled, int len, int index) {
    int left = index - 1, right = index + 1;
    while (left >= 0 || right < len) {
        if (left >= 0 && !filled[left]) return left;
        if (right < len && !filled[right]) return right;
        --left; ++right;
    }
    return -1;
}
void librarySort(TaggedValue* A, int n) {
    int bigLen = n * 2;
    TaggedValue* bigArr = new TaggedValue[bigLen];
    bool* filled = new bool[bigLen];
    std::memset(filled, 0, bigLen * sizeof(bool));

    int mid = bigLen / 2;
    bigArr[mid] = A[0];
    filled[mid] = true;

    int count = 1;

    for (int i = 1; i < n; ++i) {
        if ((i & (i - 1)) == 0) {
            TaggedValue* temp = new TaggedValue[count];
            int idx = 0;
            for (int j = 0; j < bigLen; ++j) {
                if (filled[j]) temp[idx++] = bigArr[j];
            }

            std::memset(filled, 0, bigLen * sizeof(bool));
            int gap = bigLen / (count + 1);
            int pos = gap;
            for (int j = 0; j < count; ++j) {
                bigArr[pos] = temp[j];
                filled[pos] = true;
                pos += gap;
            }

            delete[] temp;
        }

        int insertIndex = libinary(bigArr, filled, bigLen, A[i].value);

        if (!filled[insertIndex]) {
            bigArr[insertIndex] = A[i];
            filled[insertIndex] = true;
        } else {
            int nullIndex = nearNull(filled, bigLen, insertIndex);
            if (nullIndex == -1) continue;

            if (nullIndex < insertIndex) {
                if (bigArr[insertIndex].value <= A[i].value) {
                    for (int j = nullIndex; j < insertIndex; ++j) {
                        bigArr[j] = bigArr[j + 1];
                        filled[j] = filled[j + 1];
                    }
                    bigArr[insertIndex] = A[i];
                    filled[insertIndex] = true;
                } else {
                    for (int j = nullIndex; j < insertIndex - 1; ++j) {
                        bigArr[j] = bigArr[j + 1];
                        filled[j] = filled[j + 1];
                    }
                    bigArr[insertIndex - 1] = A[i];
                    filled[insertIndex - 1] = true;
                }
            } else {
                if (bigArr[insertIndex].value <= A[i].value) {
                    for (int j = nullIndex; j > insertIndex + 1; --j) {
                        bigArr[j] = bigArr[j - 1];
                        filled[j] = filled[j - 1];
                    }
                    bigArr[insertIndex + 1] = A[i];
                    filled[insertIndex + 1] = true;
                } else {
                    for (int j = nullIndex; j > insertIndex; --j) {
                        bigArr[j] = bigArr[j - 1];
                        filled[j] = filled[j - 1];
                    }
                    bigArr[insertIndex] = A[i];
                    filled[insertIndex] = true;
                }
            }
        }
        ++count;
    }

    int idx = 0;
    for (int i = 0; i < bigLen && idx < n; ++i) {
        if (filled[i]) A[idx++] = bigArr[i];
    }

    delete[] bigArr;
    delete[] filled;
}


// void rebalance(TaggedValue* S, int begin, int end) {
//     int r = end;
//     int w = 2 * end;
//     while (r >= begin) {
//         S[w] = S[r];
//         S[w - 1].value = INT_MAX;
//         S[w - 1].originalIndex = -1; // gap
//         r--;
//         w -= 2;
//     }
// }

// int binarySearchSkipGaps(TaggedValue x, TaggedValue* S, int k) {
//     int left = 1;
//     int right = k;
//     int mid;

//     while (left <= right) {
//         int l = left, r = right;

//         // skip gaps: adjust l and r to land on non-gap values
//         while (l <= r && S[l].value == INT_MAX) l++;
//         while (l <= r && S[r].value == INT_MAX) r--;
//         if (l > r) break;

//         int midCandidate = (l + r) / 2;

//         // Find actual non-gap mid by scanning outward
//         mid = midCandidate;
//         while (S[mid].value == INT_MAX && mid < r) mid++;
//         if (S[mid].value == INT_MAX) {
//             mid = midCandidate;
//             while (S[mid].value == INT_MAX && mid > l) mid--;
//             if (S[mid].value == INT_MAX) break;
//         }

//         if (x.value < S[mid].value) {
//             right = mid - 1;
//         } else {
//             left = mid + 1;
//         }
//     }

//     // Now find nearest gap from position 'left'
//     int insertPos = left;
//     while (insertPos <= k && S[insertPos].value != INT_MAX) {
//         insertPos++;
//     }
//     return insertPos;
// }

// void librarySort(TaggedValue* A, int n) {
//     const int size = 2 * n + 2; // padding
//     TaggedValue* S = new TaggedValue[size];
//     for (int i = 0; i < size; ++i) {
//         S[i].value = INT_MAX;
//         S[i].originalIndex = -1;
//     }

//     S[1] = A[0];

//     int rounds = (int)std::log2(n - 1);
//     for (int i = 1; i <= rounds; ++i) {
//         int start = 1;
//         int end = (1 << (i - 1));
//         rebalance(S, start, end);

//         for (int j = (1 << (i - 1)) + 1; j <= (1 << i) && j <= n; ++j) {
//             int pos = binarySearchSkipGaps(A[j - 1], S, (1 << i));
//             S[pos] = A[j - 1];
//         }
//     }

//     // Copy sorted non-gaps back to A
//     int idx = 0;
//     for (int i = 1; i < size; ++i) {
//         if (S[i].value != INT_MAX) {
//             A[idx++] = S[i];
//         }
//     }

//     delete[] S;
// }


// const TaggedValue GAP_TAG = { INT_MIN, -1 };

// bool isGap(const TaggedValue& tv) {
//     return tv.value == GAP_TAG.value && tv.originalIndex == GAP_TAG.originalIndex;
// }

// void rebalance(TaggedValue* S, int capacity) {
//     std::vector<TaggedValue> compact;
//     for (int i = 0; i < capacity; ++i) {
//         if (!isGap(S[i])) {
//             compact.push_back(S[i]);
//         }
//     }

//     for (int i = 0; i < capacity; ++i) {
//         S[i] = GAP_TAG;
//     }

//     int spacing = 2;  // can be adjusted
//     int idx = 0;
//     for (int i = 0; i < compact.size(); ++i) {
//         int pos = idx;
//         while (pos < capacity && !isGap(S[pos])) {
//             pos++;
//         }
//         if (pos < capacity) {
//             S[pos] = compact[i];
//         } else {
//             // should not happen with enough capacity
//         }
//         idx += spacing;
//     }
// }

// int binarySearchInsertionPos(TaggedValue* S, int size, const TaggedValue& target) {
//     int left = 0;
//     int right = size - 1;

//     while (left <= right) {
//         int mid = (left + right) / 2;

//         // skip gaps to the left
//         int midLeft = mid;
//         while (midLeft >= left && isGap(S[midLeft])) midLeft--;
//         if (midLeft < left) {
//             right = mid - 1;
//             continue;
//         }

//         if (S[midLeft].value < target.value) {
//             left = mid + 1;
//         } else if (S[midLeft].value > target.value) {
//             right = midLeft - 1;
//         } else {
//             // handle duplicates
//             while (midLeft > left && S[midLeft - 1].value == target.value) midLeft--;
//             while (midLeft < size &&
//                    S[midLeft].value == target.value &&
//                    S[midLeft].originalIndex < target.originalIndex) {
//                 midLeft++;
//             }
//             return midLeft;
//         }
//     }

//     return left;
// }

// int findEmptySlotRight(TaggedValue* S, int from, int capacity) {
//     for (int i = from; i < capacity; ++i) {
//         if (isGap(S[i])) return i;
//     }
//     return -1;
// }

// void librarySort(TaggedValue* arr, int n) {
//     if (n <= 1) return;

//     int capacity = n * 4;  // generous buffer
//     TaggedValue* S = new TaggedValue[capacity];
//     for (int i = 0; i < capacity; ++i) S[i] = GAP_TAG;

//     int itemCount = 1;
//     S[0] = arr[0];

//     for (int i = 1; i < n; ++i) {
//         if ((i & (i - 1)) == 0) {
//             rebalance(S, capacity);
//         }

//         int logicalPos = binarySearchInsertionPos(S, capacity, arr[i]);

//         // find empty spot for actual insertion
//         int insertPos = findEmptySlotRight(S, logicalPos, capacity);
//         if (insertPos == -1) {
//             // fallback: full scan
//             for (insertPos = capacity - 1; insertPos >= 0; --insertPos) {
//                 if (isGap(S[insertPos])) break;
//             }
//         }

//         // shift to the right to make room
//         for (int j = insertPos; j > logicalPos; --j) {
//             S[j] = S[j - 1];
//         }

//         S[logicalPos] = arr[i];
//         itemCount++;
//     }

//     // write back to original array
//     int idx = 0;
//     for (int i = 0; i < capacity && idx < n; ++i) {
//         if (!isGap(S[i])) {
//             arr[idx++] = S[i];
//         }
//     }

//     delete[] S;
// }

// Intro Sort
void introSortRecursive(TaggedValue* A, int lo, int hi, int depthLimit) {
    if (hi - lo <= 16) {
        insertionSort(A, lo, hi);
    } else if (depthLimit == 0) {
        heapSort(A, lo, hi);
    } else {
        int p = partition(A, lo, hi);
        introSortRecursive(A, lo, p - 1, depthLimit - 1);
        introSortRecursive(A, p + 1, hi, depthLimit - 1);
    }
}
void introSort(TaggedValue* A, int n) {
    int depthLimit = 2 * static_cast<int>(std::log2(n));
    introSortRecursive(A, 0, n - 1, depthLimit);
}

// Tim Sort
const int RUN = 32;
void timSort(TaggedValue* A, int n) {
    for (int i = 0; i < n; i += RUN)
        insertionSort(A, i, std::min(i + RUN - 1, n - 1));
    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min(left + size - 1, n - 1);
            int right = std::min(left + 2 * size - 1, n - 1);
            if (mid < right)
                merge(A, left, mid, right);
        }
    }
}