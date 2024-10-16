// Brij Malhotra
// lab5.cpp
// Purpose: This lab tests the runtime and efficiency of different sorting methods

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function prototypes
void mergeSort(int arr[], int);
void quickSort(int arr[], int);
void heapSort(int arr[], int);
void heapify(int arr[], int, int);
void percolateDown(int arr[], int, int);
void swap(int, int, int arr[]);
void deleteMax(int arr[], int);
void mergeSort(int arr[], int, int);
void merge(int arr[], int, int, int);
void quickSort(int arr[], int, int);
int partition(int arr[], int, int);
int randomizedPartition(int arr[], int, int);
void display(int arr[], int);

int main(){
    
    int size[] = {10, 100, 1000, 10000, 100000};

    cout << endl;

    for (int i = 0; i < 5; i++){
        int * unsortedArray = new int[size[i]];
        cout << "The current array size is: " << size[i] << endl << endl;
        
        for (int j = 0; j < size[i]; j++){
            unsortedArray[j] = rand() % 100000;
        }

        // Heap sort before
        cout << "Printing random array of 10 before Heap sort: " << endl;
        display(unsortedArray, size[i]);
        
        // Heap sort after
        auto startHeap = high_resolution_clock::now();
        heapSort(unsortedArray, (size[i] - 1));
        auto stopHeap = high_resolution_clock::now();
        auto durationHeap = duration_cast<nanoseconds>(stopHeap - startHeap);
        cout << "Printing random array of 10 after Heap sort: " << endl;
        display(unsortedArray, size[i]);
        cout << "Time taken to sort using Heap sort: " << durationHeap.count() << " ns" << endl << endl;

        // Randomizing array again
        for (int j = 0; j < size[i]; j++){
            unsortedArray[j] = rand() % 100000;
        }

        // Merge sort before
        cout << endl << "Printing random array of 10 before Merge sort: " << endl;
        display(unsortedArray, size[i]);

        // Merge sort after
        auto startMerge = high_resolution_clock::now();
        mergeSort(unsortedArray, size[i]);
        auto stopMerge = high_resolution_clock::now();
        auto durationMerge = duration_cast<nanoseconds>(stopMerge - startMerge);
        cout << "Printing random array of 10 after Merge sort: " << endl;
        display(unsortedArray, size[i]);
        cout << "Time taken to sort using Merge sort: " << durationMerge.count() << " ns" << endl << endl;

        // Randomizing array again
        for (int j = 0; j < size[i]; j++){
            unsortedArray[j] = rand() % 100000;
        }

        // Quick sort before
        cout << endl <<  "Printing random array of 10 before Quick sort: " << endl;
        display(unsortedArray, size[i]);

        // Quick sort after
        auto startQuick = high_resolution_clock::now();
        quickSort(unsortedArray, size[i]);
        auto stopQuick = high_resolution_clock::now();
        auto durationQuick = duration_cast<nanoseconds>(stopQuick - startQuick);
        cout << "Printing random array of 10 after Quick sort: " << endl;
        display(unsortedArray, size[i]);
        cout << "Time taken to sort using Quick sort: " << durationQuick.count() << " ns" << endl << endl;

        delete [] unsortedArray;

        cout << endl << endl;
    }
}

// Function declarations

void quickSort(int arr[], int size){
    quickSort(arr, 0, (size - 1));
}

void mergeSort(int arr[], int size){
    mergeSort(arr, 0, (size - 1));
}

void display(int arr[], int size){
    if (size == 10){
        for (int j = 0; j < size; j++){
            cout << arr[j] << ", ";
        }
        
        cout << endl << endl;
    }
}

// This functions swaps two elements of an array
void swap(int pos1, int pos2, int arr[]){
    int temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
}

// This function makes a max heap to sort the array
void heapSort(int arr[], int n){
    heapify(arr, 0, n);

    for (int i = n; i > 0; i--){
        deleteMax(arr, i);
    }
}

// This function heapify's an unsorted array into a max heap
void heapify(int arr[], int i, int size){
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;

    if (left > size){
        return;
    }

    heapify(arr, right, size);
    heapify(arr, left, size);
    percolateDown(arr, i, size);
}

// This function compares the index with its children and swaps when necessary
// in order to keep a max heap
void percolateDown(int arr[], int index, int size){
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    
    // Base cases
    if (left > size){
        return;
    }

    if (right > size){
        if (arr[index] < arr[left]){
            swap(index, left, arr);
        }
        return;
    }

    if (arr[index] > arr[right] && arr[index] > arr[left]){
        return;
    }

    // Recursive case
    if (arr[left] > arr[right]){
        swap(index, left, arr);
        percolateDown(arr, left, size);
    } else {
        swap(index, right, arr);
        percolateDown(arr, right, size);
    }
}

// This function deletes the root of a max heap
void deleteMax(int arr[], int size){
    if (size == -1){
        return;
    }

    swap(0, size, arr);
    size--;
    percolateDown(arr, 0, size);
}

// Function merges the temp arrays to create the sorted array
void mergeSort(int arr[], int start, int end){
    
    // Base case along with recursive step
    if (start < end){
        int mid = (start + end)/2;
        mergeSort(arr, start, mid);
        mergeSort(arr, (mid + 1), end);
        merge(arr, start, mid, end);
    }
}

// Function halves the array to sort it
void merge(int arr[], int start, int mid, int end){
    
    // Temporary subarrays to use for merging, Left and Right
    int * L = new int[mid - start + 1];
    int * R = new int[end- mid];

    // Putting first half of array into the left subarray
    for (int i = 0; i < (mid - start + 1); i++){
        L[i] = arr[start + i];
    }

    // Putting second half of array into the right subarray
    for (int i = 0; i < (end - mid); i++){
        R[i] = arr[i + mid + 1];
    }

    int i = 0; // Tracks values of Left subarray
    int j = 0; // Tracks values of Right subarray
    int k = start; // Tracks values of main array

    // Merge from L and R while comparing values to the initial array
    while (i < (mid - start + 1) && j < (end - mid)){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Sending the rest of the Left subarray to the initial array
    while (i < (mid - start + 1)){
        arr[k] = L[i];
        i++;
        k++;
    }

    // Sending the rest of the Right subarray to the initial array
    while (j < (end - mid)){
        arr[k] = R[j];
        j++;
        k++;
    }

    // Deallocating the temp subarrays created within the function
    delete [] L;
    delete [] R;
}

// This function calls the partition functions to sort the array
void quickSort(int arr[], int i, int j){
    if (i < j){
        int pivotIndex = randomizedPartition(arr, i, j);
        quickSort(arr, i, (pivotIndex - 1));
        quickSort(arr, (pivotIndex + 1), j);
    }
}

// This function moves elements of the index based on its value compared to the pivot
int partition(int arr[], int i, int j){
    int p = arr[i];
    int m = i;

    for (int k = i + 1; k <= j; k++){
        if (arr[k] <= p){
            m++;
            swap(k, m, arr);
        }
    }
    swap(i, m, arr);
    return m;
}

// This function chooses a random pivot for the Quick sort
int randomizedPartition(int arr[], int i, int j){
    int pos = i + rand() % (j - i + 1);
    swap(i, pos, arr);
    return partition(arr, i, j);
}