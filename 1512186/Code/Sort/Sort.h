#pragma once

#include <iostream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;
class Sort {
public:
	virtual void sort(int*a, int n)=0;
};

class SelectionSort : public Sort {
public:
	void sort(int*a, int n);
};

class BubbleSort : public Sort {
public:
	void sort(int*a, int n);
};

class InsertionSort : public Sort {
public:
	void sort(int*a, int n);
};

class MergeSort : public Sort {
public:
	void merge(int*a, int l, int m, int r);
	void mergeSort(int*a, int l, int r);
	void sort(int*a, int n);
};

class QuickSort : public Sort {
public:
	int partition(int*a, int low, int high);
	void quickSort(int* a, int low, int high);
	void sort(int*a, int n);
};

class HeapSort : public Sort {
public:
	void heapify(int*a, int n, int i);
	void sort(int*a, int n);
};

class RadixSort : public Sort {
public:
	int getMax(int*a, int n);
	void countSort(int*a, int n, int exp);
	void sort(int*a, int n);
};

class RunSort {
	Sort*s;
public:
	RunSort();
	void setRunSort(Sort* _s);
	void getResult(int*a, int n);
};


void GenerateRandomData(int* a, int n);
void GenerateSortedData(int* a, int n);
void GenerateReverseData(int* a, int n);
void GenerateNearSortedData(int* a, int n);

void writeFileTxt(string s, int*a, int n);
string createNameFile(int alg, int state, int s);
float getTime(RunSort run, int*a, int n, int alg, int state);