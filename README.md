# UNIST CSE331: Introduction to Algorithms - Assignment 1

## Overview

This repository contains the source code and experimental results for **Assignment 1** of the course **CSE331: Introduction to Algorithms** at UNIST. The assignment focuses on implementing, analyzing, and benchmarking various sorting algorithms, ranging from conventional to contemporary approaches.

The repository is linked to the accompanying report, which provides detailed explanations, pseudocode, complexity analysis, and experimental results for each algorithm.

## Contents

### Folder Structure

- `src/`: Contains the source code for all sorting algorithms implemented in C++.

  - Each algorithm is modularized for easy testing and benchmarking.
  - Includes implementations for:
    - Conventional algorithms: Bubble Sort, Selection Sort, Insertion Sort, Quick Sort, Heap Sort, Merge Sort.
    - Contemporary algorithms: Cocktail Shaker Sort, Comb Sort, Tournament Sort, Library Sort, Intro Sort, Tim Sort.

- `test/`: Contains test files and input data for benchmarking.

  - Input files are categorized by type (random, sorted, reverse sorted, partially sorted) and size in `test/testCase`.
  - Test cases are repeated 10 times for averaging results.

- `results/`: Stores the experimental results, including execution time, memory usage, correctness, and stability for each algorithm.

- `docs/`: Contains the LaTeX source and compiled PDF of the report detailing the experimental analysis.

- `README.md`: This file, providing an overview of the repository and its structure.

## Experimental Design

The benchmarking framework evaluates sorting algorithms based on the following metrics:

1. **Correctness**: Ensures the output is sorted in non-decreasing order.
2. **Stability**: Verifies that equal elements retain their relative order.
3. **Execution Time**: Measures the time taken to sort arrays of varying sizes and types.
4. **Memory Usage**: Tracks the additional memory required during sorting.

### Input Data

- Input sizes: \(10^3\), \(10^4\), \(10^5\), \(10^6\).
- Input types: Random, sorted, reverse sorted, partially sorted.
- File naming convention: `type_size_trial.txt` (e.g., `random_1000_4.txt`).

### Algorithms Implemented

#### Conventional Sorting Algorithms

- **Bubble Sort**: Simple but inefficient; used for educational purposes.
- **Selection Sort**: In-place but unstable; minimizes swaps.
- **Insertion Sort**: Efficient for small or nearly sorted data.
- **Quick Sort**: Fast on average; optimized with median-of-three pivoting.
- **Heap Sort**: Guarantees \( \mathcal{O}(n \log n) \) performance.
- **Merge Sort**: Stable and consistent; uses auxiliary memory.

#### Contemporary Sorting Algorithms

- **Cocktail Shaker Sort**: Bidirectional Bubble Sort variant.
- **Comb Sort**: Improves Bubble Sort with gap-based comparisons.
- **Tournament Sort**: Uses a winner tree for efficient selection.
- **Library Sort**: Gapped Insertion Sort for reduced shifting.
- **Intro Sort**: Hybrid of Quick, Heap, and Insertion Sort.
- **Tim Sort**: Adaptive hybrid sort; excels on real-world data.

## Results Summary

### Execution Time

- **Tim Sort** and **Intro Sort** consistently performed best across all input types and sizes.
- **Quick Sort** with median-of-three pivoting (Quick2) showed robust performance.
- Quadratic algorithms (Bubble, Selection, Insertion) were only feasible for small inputs.

### Memory Usage

- In-place algorithms (Quick, Intro) used minimal memory.
- Merge-based algorithms (Merge, Tim) required additional auxiliary space.

### Stability

- Stable algorithms: Bubble, Insertion, Merge, Cocktail, Library, Tim.
- Unstable algorithms: Selection, Quick, Heap, Comb, Tournament, Intro.

For detailed results and analysis, refer to the [report](docs/report.pdf).

## Author

- Name: Doyeol Oh
- Student ID: 20211187
- Email: ohdoyoel@unist.ac.kr

## License

This project is for educational purposes only. Redistribution or use for other purposes is prohibited.
