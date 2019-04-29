//Read file
//Determine which algorithm to use
//make vector out of the numbers in the file afte the first two
//sort them
//output the sorted list to another file

#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>

void merge(int* list, int left, int middle, int right)
{
    int sub = middle + 1;

    if (list[middle] <= list[sub]) {
        return;
    }

    while (left <= middle && sub <= right) {
        if (list[left] <= list[sub]) {
            left++;
        }
        else {
            int val = list[sub];
            int index = sub;

            while (index != left) {
                list[index] = list[index - 1];
                index--;
            }
            list[left] = val;

            left++;
            middle++;
            sub++;
        }
    }
}

int partition(int* list, int lo, int hi)
{
    int pivot = list[hi];
    int s = lo - 1;

    for (int j = lo; j <= hi - 1; j++) {
        if (list[j] <= pivot) {
            s++;
            int temp = list[s];
            list[s] = list[j];
            list[j] = temp;
        }
    }
    int temp = list[s + 1];
    list[s + 1] = list[hi];
    list[hi] = temp;
    return s + 1;
}

void selectionSort(int* list, int size) 
{
    for (int i = size - 1; i >= 1; i--){
        int max = 0;
        for (int j = 1; j <= i; j++) {
            if (list[j] > list[max]) { 
                max = j;
            }
        }
        if (max != i) {
            int temp = list[max];
            list[max] = list[i];
            list[i] = temp;
        }
    }
}

void insertionSort(int* list, int size)
{
    for (int i = 1; i <= size - 1; i++) {
        int j = i - 1;
        int temp = list[i];
        while (j >= 0 && temp < list[j]) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = temp;
    }
}


void bubbleSort(int* list, int size) 
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (list[j] > list[j+1]) {
                int temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}

void mergeSort(int* list, int left, int right) 
{
    if (left < right) { 
        int middle = left + (right - left) / 2; 
        mergeSort(list, left, middle); 
        mergeSort(list, middle + 1, right); 
  
        merge(list, left, middle, right); 
    } 
}

void quickSort(int* list, int first, int last) 
{
    if (first < last) {
        int p = partition(list, first, last);

        quickSort(list, first, p - 1);
        quickSort(list, p + 1, last);
    }
}

int main(int argc, char const *argv[])
{
    if (argc == 1) {
        std::cout << "need an argument";
        return 1;
    }

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    int64_t timeTaken;
    int whichAlg;
    int size;
    int curr;
        
    std::ifstream file(argv[1]);
    std::ofstream output("sorted.txt");
    if (file.is_open()) {

        file >> whichAlg;
        file >> size;
        int* list;
        list = new int[size];

        for (int i = 0; i < size; i++) {
            file >> curr;
            *(list + i) = curr;
        }

        switch (whichAlg) {
            case 1:
                begin = std::chrono::steady_clock::now();
                selectionSort(list, size);
                end= std::chrono::steady_clock::now();
                break;
            case 2:
                begin = std::chrono::steady_clock::now();
                insertionSort(list, size);
                end = std::chrono::steady_clock::now();
                break;
            case 3:
                begin = std::chrono::steady_clock::now();
                bubbleSort(list, size);
                end = std::chrono::steady_clock::now();
                break;
            case 4:
                begin = std::chrono::steady_clock::now();
                mergeSort(list, 0, size - 1);
                end = std::chrono::steady_clock::now();
                break;
            case 5:
                begin = std::chrono::steady_clock::now(); 
                quickSort(list, 0, size - 1);
                end = std::chrono::steady_clock::now();
                break;
            default:
                std::cout << "You shouldnt see this" << '\n';
        }

        timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

        output << whichAlg << '\n';
        output << size << '\n';
        for (int i = 0; i < size; i++) {
            output << list[i] << '\n';
        }
    }
    else {
        std::cout << "file not found" << '\n';
    }
    std::cout << "Time taken is " << timeTaken << '\n';
    return 0;
}

