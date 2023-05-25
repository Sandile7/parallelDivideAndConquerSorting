/*
 * Author: Sandile Ngwenya
 * Parallel Quick Sort algorithm to be compared with the Serial Quick Sort.
 * This is a program that sorts an array of integers using the quicksort 
 * algorithm, using multithreading to speed up the sorting process.
 * This is achieved through pthreads, and mutex locks for synchronization.
 * Functions: quicksort(args), main(argc, argv).
 * Libraries: stdio.h, stdlib.h, time.h, pthread.h
 */

// Libraries.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/*
 * struct called quicksort_args_t
 * Fields: array of integers, left and right indices of the subarray to be sorted, 
 * the recursion depth of the quicksort algorithm and pthread_mutex_t lock.
 */
typedef struct {
    int *array;
    int left;
    int right;
    int depth;
    pthread_mutex_t lock;
} quicksort_args_t;

// Functions
void *quicksort(void *args_ptr);

// main
int main(int argc, char *argv[]) {
    // Declare and define variables to be used, time, i and array size
    double start, end; 
    double cpu_time_used;
    int i;

    // Input number of threads from terminal
    if (argc < 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }
    int num_threads = atoi(argv[1]); // number of threads variable 

    // Sizes of array to be tested
    //int arraySize = 10;
    //int arraySize = 1000;
    //int arraySize = 2000;
    //int arraySize = 4000;
    //int arraySize = 8000;
    int arraySize = 16000;

    int array[arraySize];
    
    // Open the input file for binary read mode
    //FILE *fp = fopen("test10.txt", "rb");
    //FILE *fp = fopen("test1000.txt", "rb");
    //FILE *fp = fopen("test2000.txt", "rb");
    //FILE *fp = fopen("test4000.txt", "rb");
    //FILE *fp = fopen("test8000.txt", "rb");
    FILE *fp = fopen("test16000.txt", "rb");

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
    }// unsorted for
    printf("\n");

    pthread_t threads[num_threads]; // define threads variable

    // Initialize quicksort arguments struct with the input array, left index, right index, depth, and a mutex lock.
    quicksort_args_t args = {array, 0, arraySize - 1, 0, PTHREAD_MUTEX_INITIALIZER};
    
    // Create threads and pass the same quicksort arguments to each thread
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, quicksort, &args);
    }// for create

    // Wait for all threads to complete before continuing
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }// for join

    printf("Sorted array: \n");
    // Print orted array
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
 * Function takes a void pointer to a quicksort_args_t struct as its argument
 * Purpose of function is to parallelize the quick sorting algorithm in a recursive manner.
 */
void *quicksort(void *args_ptr) {
    // Cast it to the appropriate type
    quicksort_args_t *args = (quicksort_args_t *) args_ptr;

    // Extract the relevant fields from the struct and declare other variables
    int *array = args->array;
    int left = args->left;
    int right = args->right;
    int depth = args->depth;
    int i = left, j = right;
    int temp;
    int pivot = array[(left + right) / 2];

    pthread_mutex_lock(&args->lock); // Lock the mutex for synchronization
    
    // Run until indices i and j cross each other
    while (i <= j) {
        // Increment index i until finds an element that is not less than the pivot
        while (array[i] < pivot) {
            i++;
        }// increment i
        // Decrement index j until finds an element that is not greater than the pivot
        while (array[j] > pivot) {
            j--;
        }// decrement j
        // Swap the elements at indices i and j if i is less than or equal to j
        if (i <= j) {
            // critical block
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }// swap
    }// while loop for cross

    pthread_mutex_unlock(&args->lock); // Unlock the mutex

    // Recursively sort the left segment of the array
    if (left < j) {
        // New argument struct for the left segment of the array
        quicksort_args_t args_left = {array, left, j, depth + 1};
        // Call quicksort recursively for the left segment
        quicksort(&args_left);
    }// left seg

    // Recursively sort the right segment of the array
    if (i < right) {
        // New argument struct for the right segment of the array
        quicksort_args_t args_right = {array, i, right, depth + 1};
        // Call quicksort recursively for the right segment
        quicksort(&args_right);
    }// right seg

    pthread_exit(NULL); // exit thread
}//quicksort
