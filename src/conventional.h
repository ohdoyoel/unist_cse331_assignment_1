#pragma once
#include "type.h"

void bubbleSort(TaggedValue* A, int n);
void selectionSort(TaggedValue* A, int n);
void insertionSort(TaggedValue* A, int left, int right);
void insertionSort(TaggedValue* A, int n);
int partition(TaggedValue* A, int low, int high);
void quickSort(TaggedValue* A, int n);
void quickSort2(TaggedValue* A, int n);
void heapSort(TaggedValue* A, int low, int high);
void heapSort(TaggedValue* A, int n);
void merge(TaggedValue* A, int left, int mid, int right);
void mergeSort(TaggedValue* A, int n);