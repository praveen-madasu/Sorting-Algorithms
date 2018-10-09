/*
	Sorting Algorithms.cpp
	Tools Used: Dev C++ Version 5.11
	Compiler Options: -static-libgcc -std=c++11
	ITCS 6114 Algorithms & Data Structures
	Authors: Shanmukha Praveen Madasu, Narendra Kumar Vankayala
*/

//#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <chrono>

#include<bits/stdc++.h>

using namespace std;

//Uncomment one and comment another to evaluate the special cases like sorted & reverse sorted array
//#define sortedOrder				1
//#define reverseSortedOrder	1

void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

//Insertion sort algorithm
void insertionSort(int arr[], int n)
{
	int key, i, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;
		for (; j >= 0 && (arr[j] > key); j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}

void merge(int arr[], int low, int med, int high)
{
	int *temp = new int[high - low + 1];
	int i = low, j = med + 1, k = 0;

	while (i <= med && j <= high)
	{
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}

	while (i <= med)
		temp[k++] = arr[i++];

	while (j <= high)
		temp[k++] = arr[j++];

	for (k = 0, i = low; i <= high; ++k, ++i)
	{
		arr[i] = temp[k];
	}

	delete[]temp;
}

void mergeSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int med = (low + high) / 2;
		mergeSort(arr, low, med);
		mergeSort(arr, med + 1, high);
		merge(arr, low, med, high);
	}
}

void quickSortInPlace(int a[], int low, int high)
{
	int i = low + 1;
	int j = high;
	int pivot = a[low];

	while (i <= j)
	{
		while (a[i] < pivot)
		{
			i++;
		}
		while (a[j] > pivot)
		{
			j--;
		}

		if (i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	swap(a[j], a[low]);

	if (low < j)
		quickSortInPlace(a, low, j);
	if (i < high)
		quickSortInPlace(a, i, high);
}

//partition function used by modified quickSort algorithm
int partition(int a[], int low, int high)
{
	int left, right;
	int pivot;

	left = low;
	right = high;
	pivot = a[low];

	while (left < right)
	{
		while (a[right] > pivot)
			right--;

		while ((left < right) && (a[left] <= pivot))
			left++;

		if (left < right)
			swap(a[left], a[right]);
	}

	a[low] = a[right];
	a[right] = pivot;

	return right;
}

//medain as pivot
int median(int a[], int low, int high)
{
	int middle = (low + high) / 2;

	if (a[low] > a[middle])
		swap(a[middle], a[low]);
	if (a[low] > a[high])
		swap(a[low], a[high]);
	if (a[middle] > a[high])
		swap(a[high], a[middle]);

	swap(a[middle], a[low]);

	return partition(a, low, high);
}

//quicksort median of three
void modifiedQuickSort(int a[], int low, int high, int size)
{
	int pivotPosition;

	if ((size > 10)  && (low < high))
	{
		pivotPosition = median(a, low, high);
		modifiedQuickSort(a, low, pivotPosition - 1,size);
		modifiedQuickSort(a, pivotPosition + 1, high,size);
	}
	else if (size <= 10)
	{
		insertionSort(a, size);
	}
}


int main()
{
	int arr[10] = {  500,  1000,  2000,  4000,  5000,  10000,  20000,  30000,  40000 , 50000 };
	int size;
	for(int i =0 ; i< 10; i++){
		size = arr[i];
		

	//For generating random numbers of size length
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, size);

	int a[size] = {0};
	int insArr[size], mergeArr[size], inPlaceQuickArr[size], medianQuickArr[size] = {0};

	for (int i = 0; i < size; i++)
	{
		a[i] = dis(gen);;
	}
	cout << endl;

	#ifdef sortedOrder		//This will only get compiled when the corresponding #define is enabled
		//sorted array
		sort(a, a + size);
	#endif // sortedOrder

	#ifdef reverseSortedOrder
		//Reverse sorted array	//This will only get compiled when the corresponding #define is enabled
		sort(a, a + size, greater<int>());
	#endif // reverseSortedOrder
	
	for (int i = 0; i < size; i++)
	{
		insArr[i] = a[i];
		mergeArr[i] = a[i];
		inPlaceQuickArr[i] = a[i];
		medianQuickArr[i] = a[i];
	}

	cout << "Input size: " << size << endl;

	//Insertion Sort
	auto start = chrono::steady_clock::now();
	insertionSort(insArr, size);
	auto stop = chrono::steady_clock::now();
	cout << "Insertion Sort Execution time:		" << chrono::duration_cast<chrono::nanoseconds>(stop - start).count() << "ns\n";

	//Merge Sort
	start = chrono::steady_clock::now();
	mergeSort(mergeArr, 0, size - 1);
	stop = chrono::steady_clock::now();
	cout << "Merge Sort Execution time:		" << chrono::duration_cast<chrono::nanoseconds>(stop - start).count() << "ns\n";
	
	//In-Place Quick Sort
	start = chrono::steady_clock::now();
	quickSortInPlace(inPlaceQuickArr, 0, size - 1);
	stop = chrono::steady_clock::now();
	cout << "In-Place Quick Sort Execution time:	" << chrono::duration_cast<chrono::nanoseconds>(stop - start).count() << "ns\n";

	//Modified Quick Sort
	start = chrono::steady_clock::now();
	modifiedQuickSort(medianQuickArr, 0, size - 1,size);
	stop = chrono::steady_clock::now();
	cout << "Modified Quick Sort Execution time:	" << chrono::duration_cast<chrono::nanoseconds>(stop - start).count() << "ns\n";
	}
}


