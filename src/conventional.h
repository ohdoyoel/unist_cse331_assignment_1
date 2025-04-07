#pragma once
#include <vector>

void bubbleSort(std::vector<int>& arr);
void selectionSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr, int left, int right);
void heapSort(std::vector<int>& arr);
void heapSort(std::vector<int>& arr, int left, int right);
void merge(std::vector<int>& arr, int left, int mid, int right);
void mergeSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr);