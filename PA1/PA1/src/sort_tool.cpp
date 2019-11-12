// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    // for(int i=0; i<data.size(); i++) cout << "data "  << i << " = " << data.at(i) << endl;
    for(int i=1; i<data.size(); i++){
        int j = i-1;
        int x = data[i];
        while(x < data[j] && j >= 0){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = x;
    }
    // cout << "data = " << endl;
    // for(int i=0; i<data.size(); i++) cout << data.at(i) << " ";
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low < high){
        int q = Partition(data, low, high);
        QuickSortSubVector(data, low, q-1);
        QuickSortSubVector(data, q+1, high);
    }
}
int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int x = data.at(high);
    int i = low -1;
    for (int j = low; j < high; j++) {
        if (data[j] < x) {
            i++;
            swap(data.at(i), data.at(j));
        }
    }
    i++;
    swap(data.at(i), data.at(high));
    return i;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high) {
		int m = (low + high) / 2;
		MergeSortSubVector(data, low, m);  
		MergeSortSubVector(data, m+1, high); 
		Merge(data, low, m, 0, high);
	}
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle1 - low + 1;
    int n2 = high - middle1;
    int* L = new int[n1+1];
	int* R = new int[n2+1];

	for(int i = 0; i < n1; i++) L[i] = data[low+i]; 
	for(int i = 0; i < n2; i++) R[i] = data[middle1+i+1]; 
	L[n1] = 2147483647;
	R[n2] = 2147483647;
    int i = 0, j = 0;
	for(int k = low; k <=high; k++){
		if(L[i] <= R[j]){
			data[k] = L[i];
			i++;
		}
		else{
			data[k] = R[j];
			j++;
		}
	}
}


// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = 2*root + 1;
    int r = 2*root + 2;
    int largest;
    if(l < heapSize && data[l] > data[root]) largest = l;
    else largest = root;

    if(r < heapSize && data[r] > data[largest]) largest = r;

    if (largest != root) {
        swap(data.at(largest), data.at(root));
        MaxHeapify(data, largest); 
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = (heapSize/2)-1; i >= 0 ; i--) {
        MaxHeapify(data, i);
    }
}
