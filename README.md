# 📘 UNIST CSE331: Introduction to Algorithms - Assignment 1

> ✨ A comparative study of classical and modern sorting algorithms, implemented and analyzed from scratch.

---

## 📂 Repository Overview

This repository contains the **source code** and **experimental results** for **Assignment 1** of **CSE331: Introduction to Algorithms** at UNIST. The project implements, benchmarks, and analyzes a wide range of sorting algorithms—both conventional and contemporary.

📄 For full explanations, pseudocode, complexity analysis, and benchmarking methodology, refer to the detailed [report](docs/report.pdf).

---

## 📁 Folder Structure

```
.
├── src/         # 💻 Source code (C++) for sorting algorithms
├── test/        # 🧪 Input files for benchmarking
├── results/     # 📊 Benchmark results (execution time, memory, etc.)
├── docs/        # 📚 Report LaTeX source & PDF
└── README.md    # 📝 This file
```

### 🔧 `src/`
- Modular C++ implementations of:
  - **Conventional**: Bubble, Selection, Insertion, Quick, Heap, Merge
  - **Contemporary**: Cocktail Shaker, Comb, Tournament, Library, Intro, Tim

### 🧪 `test/`
- Input arrays categorized by:
  - Type: Random, Sorted, Reverse Sorted, Partially Sorted
  - Size: (10^3), (10^4), (10^5), (10^6)
- Repeated **10 trials** per case (e.g., `random_1000_4.txt`)

### 📊 `results/`
- Logs of:
  - ✅ Correctness
  - ♻️ Stability
  - ⏱ Execution Time
  - 🧠 Memory Usage

---

## 🧪 Experimental Design

Each sorting algorithm is evaluated across four key metrics:

| Metric           | Description                                        |
|------------------|----------------------------------------------------|
| ✅ **Correctness**    | Ensures the output is in non-decreasing order     |
| ♻️ **Stability**      | Verifies if equal elements retain original order |
| ⏱ **Execution Time** | Time taken for various sizes & input types       |
| 🧠 **Memory Usage**   | Tracks auxiliary memory consumption              |

---

## 🧮 Algorithms Implemented

### 📚 Conventional Sorting

- 🔵 **Bubble Sort** – Simple but inefficient
- 🔵 **Selection Sort** – In-place, but not stable
- 🔵 **Insertion Sort** – Great for small or nearly sorted data
- 🔵 **Quick Sort** – Median-of-three pivot, fast average-case
- 🔵 **Heap Sort** – Guaranteed \( \mathcal{O}(n \log n) \)
- 🔵 **Merge Sort** – Stable and reliable; uses extra space

### 🚀 Contemporary Sorting

- 🟢 **Cocktail Shaker Sort** – Bi-directional bubble variant
- 🟢 **Comb Sort** – Gap-based bubble enhancement
- 🟢 **Tournament Sort** – Winner-tree based selection
- 🟢 **Library Sort** – Gapped insertion, fewer shifts
- 🟢 **Intro Sort** – Hybrid: Quick + Heap + Insertion
- 🟢 **Tim Sort** – Adaptive hybrid (Merge + Insertion); excels on partially sorted real-world data; used in Python/Java

---

## 📈 Summary of Results

📈 **All experiments were repeated 10 times per case**, across 4 input types and 4 input sizes, totaling **160 test files**, you can check them [here](test/testCase).

### ⏱ Execution Time
- 🥇 **Tim Sort** and **Intro Sort** consistently led across sizes/types
- 🥈 **Quick2 Sort** (Quick Sort with median-of-three pivot) performed robustly
- 🐢 Quadratic sorts (Bubble, Selection, Insertion) only viable for small inputs

### 📊 Benchmark Highlights in Execution Time

| Input Type        | 🥇 Best Algorithm(s)               | Notes                                             |
|-------------------|------------------------------------|---------------------------------------------------|
| Random            | Tim, Quick2, Intro                 | Tim and Quick2 balanced speed and memory usage   |
| Sorted            | Insertion, Cocktail, Tim           | Insertion was fastest due to low comparison count|
| Reverse Sorted    | Comb, Tim, Quick2                  | Comb outperformed others by handling "turtles"   |
| Partially Sorted  | Tim, Quick2, Intro, Comb           | Adaptive strategies showed best performance      |

### 🧠 Memory Usage
- 🧩 In-place sorts (Quick, Intro) were most memory-efficient
- 💾 Merge-based algorithms required additional memory

### ♻️ Stability

#### 🏷 Data Structure Used for Stability Check

All elements are wrapped in a `TaggedValue` struct, see [here](src/type.h):

```cpp
struct TaggedValue {
    int value;
    int originalIndex;
};
```

| Algorithm Type     | Algorithms                                         |
|--------------------|----------------------------------------------------|
| ✅ Stable       | Bubble, Insertion, Merge, Cocktail, Library, Tim                                             |
| ❌ Unstable     | Selection (8/16), Quick (11/16), Heap (12/16), Comb (8/16), Tournament (5/16), Intro (12/16) |

---

## ✅ Final Recommendations

| Use Case                  | Recommended Algorithm |
|---------------------------|------------------------|
| Small Sorted Inputs       | Insertion Sort         |
| Large Random Inputs       | Tim or Intro Sort      |
| Reverse Sorted Data       | Comb Sort              |
| Stability Required        | Tim or Merge Sort      |
| Low Memory Environment    | Quick2 or Intro Sort   |

---

## 🔄 Appendix: Tim2 – A Parallel Variant of Tim Sort

To explore parallelization, a multithreaded Tim Sort (Tim2) was developed using std::thread.

However, benchmark results revealed:
- ⛔ Slower than standard Tim Sort on small/medium inputs, see [Tim vs Tim2](result/~.h).
- ⚠️ Caused instability and memory spikes without thread pooling or granularity thresholds

🔍 **Future improvement**: Use OpenMP or task-based libraries (TBB) with resource-aware scheduling.

---

## 👨‍💻 Author

- **Name**: Doyeol Oh  
- **Student ID**: 20211187  
- **Email**: [ohdoyoel@unist.ac.kr](mailto:ohdoyoel@unist.ac.kr)

---

## 📜 License

This project is intended **strictly for educational use** under CSE331 at UNIST.  
Redistribution or use outside the scope of this purpose is **not permitted**.

---
