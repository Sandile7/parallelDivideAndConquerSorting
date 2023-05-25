/*
 * Author: Sandile Ngwenya
 * Code to generate random numbers that will be placed to an array 
 * in an external file. 
 */
// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//main
int main() {
    //Define and declare variables to be used, i, arraySize
    int i;

    int arraySize = 10;
    //int arraySize = 1000;
    //int arraySize = 2000;
    //int arraySize = 4000;
    //int arraySize = 8000;
    //int arraySize = 16000;
    int array[arraySize];
    
    // Seed the random number generator
    srand(time(NULL));

    // Fill the array with random numbers
    for (i = 0; i < arraySize; i++) {
        array[i] = rand() % 100; // Generate a random number between 0 and 99
    }// for fill

    // Write the array to a file
    FILE *fp = fopen("test10.txt", "wb"); // Open size 10
    //FILE *fp = fopen("test1000.txt", "wb"); // Open size 1000
    //FILE *fp = fopen("test2000.txt", "wb"); // Open size 2000
    //FILE *fp = fopen("test4000.txt", "wb"); // Open size 4000
    //FILE *fp = fopen("test8000.txt", "wb"); // Open size 8000
    //FILE *fp = fopen("test16000.txt", "wb"); // Open size 16000

    // test if a success
    if (fp == NULL) {
        fprintf(stderr, "Failed to open output file.\n"); // print error if failed
        return 1;
    }

    fwrite(array, sizeof(int), arraySize, fp); // Write the array to the file
    fclose(fp); // Close the file
    return 0;
}// main