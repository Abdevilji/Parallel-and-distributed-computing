#include<bits/stdc++.h>
#include <omp.h>
#include<chrono>

using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort serial implementation
void quickSortSerial(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortSerial(arr, low, pi - 1);
        quickSortSerial(arr, pi + 1, high);
    }
}

// Quick Sort parallel implementation
void quickSortParallel(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        #pragma omp parallel sections
        {
            #pragma omp section
            quickSortParallel(arr, low, pi - 1);
            
            #pragma omp section
            quickSortParallel(arr, pi + 1, high);
        }
    }
}

int main() {
    vector<int> sizes = {1000, 10000, 100000};

    for (int N : sizes) {
        vector<int> arr(N);

        srand(time(0));
        for (int i = 0; i < N; ++i)
            arr[i] = rand() % 10000;

        vector<int> arr_parallel = arr;

        // Quick Sort
        auto start_quick_serial = chrono::high_resolution_clock::now();
        quickSortSerial(arr, 0, N - 1);
        auto end_quick_serial = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_quick_serial = end_quick_serial - start_quick_serial;

        auto start_quick_parallel = chrono::high_resolution_clock::now();
        quickSortParallel(arr_parallel, 0, N - 1);
        auto end_quick_parallel = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_quick_parallel = end_quick_parallel - start_quick_parallel;

        cout << "Number of Elements: " << N << "\n";
        cout << "Quick Sort Serial Execution Time (Sec): " << elapsed_quick_serial.count() << "\n";
        cout << "Quick Sort Parallel Execution Time (Sec): " << elapsed_quick_parallel.count() << "\n\n";
    }

  return 0;
}