/*
 * Author: Sandile Ngwenya
 * Serial quick sort algorithm to be compared with Parallel quick sort algorithm
 * Code taken from https://www.programiz.com/dsa/quick-sort
 * Editions on time taken to sort an array
 * 
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Functions
void swap(int* a, int* b);
int partition(int arr[], int low, int high);
void quicksort(int arr[], int low, int high);

// main
int main() {
    // Declare and define variables to be used, time, i and array size
    double start, end;
    double cpu_time_used;
    int i;

    int arraySize = 10;
    //int arraySize = 1000;
    //int arraySize = 2000;
    //int arraySize = 4000;
    //int arraySize = 8000;
    //int arraySize = 16000;
    int array[arraySize];
    
    // Open the input file for binary read mode
    FILE *fp = fopen("test10.txt", "rb");
    //FILE *fp = fopen("test1000.txt", "rb");
    //FILE *fp = fopen("test2000.txt", "rb");
    //FILE *fp = fopen("test4000.txt", "rb");
    //FILE *fp = fopen("test8000.txt", "rb");
    //FILE *fp = fopen("test16000.txt", "rb");

    // Test if read was a success
    if (fp == NULL) {
        fprintf(stderr, "Failed to open input file.\n"); // print error
        return 1;
    }

    // Read the array from the file
    fread(array, sizeof(int), arraySize, fp);

    // Close the file
    fclose(fp);
    
    // Start timer
    start = clock();
    printf("Unsorted array: \n");
    // Print unsorted array
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", array[i]);
    }// for unsorted
    printf("\n");

    quicksort(array, 0, arraySize - 1); // quicksort

    printf("Sorted array: \n");
    // Print sorted
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", array[i]);
    }// for sorted
    printf("\n");

    // End clock
    end = clock();
    cpu_time_used = ((double)(end - start))/ CLOCKS_PER_SEC; // calculate run time
    // print the longest common subsequence and free memory
    printf("Time (in seconds) taken by the program to sort: %f\n", cpu_time_used);
    return 0;
}// main

/*
 * swap(int* a, int* b)
 * Function to swap elements
 */ 
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}// swap

/* 
 * partition(int arr[], int low, int high) -> int position
 * Function to find the partition position
 */ 
int partition(int arr[], int low, int high) {
    // select the rightmost element as pivot
    int pivot = arr[high];
    // pointer for greater element
    int i = (low - 1);
    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(&arr[i], &arr[j]);
        }// if pivot
    }// for compare
    // swap the pivot element with the greater element at i
    swap(&arr[i + 1], &arr[high]);
    // return the partition point
    return (i + 1);
}// partition

/*
 * quicksort(int arr[], int low, int high)
 * Function that runs the quicksort algorithm
 */
void quicksort(int arr[], int low, int high) {
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    if (low < high) {
        int pi = partition(arr, low, high);
        // recursive call on the left of pivot
        quicksort(arr, low, pi - 1);
        // recursive call on the right of pivot
        quicksort(arr, pi + 1, high);
    }// if
}// quicksort