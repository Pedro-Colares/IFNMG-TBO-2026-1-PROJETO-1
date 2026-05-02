#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
using namespace std;

template<typename T>
void MergeSort(vector<T>& L, int e, int d, bool (*compara)(T, T));

template<typename T>
void Merge(vector<T>& L, int e, int m, int d, bool (*compara)(T, T));

#include "MergeSort.cpp"

#endif