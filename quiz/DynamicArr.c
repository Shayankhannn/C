/*
 * File: array_file_stats.c
 *
 * Description:
 * This program reads integers from an input file. The first integer
 * specifies how many values will follow. A dynamic array is created
 * to store the values, and the program computes the average and maximum.
 *
 * The results are printed to the screen and also written to a file
 * named "answer-hw3.txt".
 */

#include <stdio.h>
#include <stdlib.h>

/* Compute average */
double computeAverage(int data[], int size) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += data[i];
    }

    return (double)sum / size;
}

/* Compute maximum */
int computeMax(int data[], int size) {
    int max = data[0];

    for (int i = 1; i < size; i++) {
        if (data[i] > max)
            max = data[i];
    }

    return max;
}

int main() {

    FILE *inputFile;
    FILE *outputFile;

    int size;

    inputFile = fopen("input.txt", "r");

    if (inputFile == NULL) {
        printf("Error: cannot open input file.\n");
        return 1;
    }

    /* Read size first */
    fscanf(inputFile, "%d", &size);

    /* Create dynamic array */
    int *data = (int*)malloc(size * sizeof(int));

    if (data == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* Read values */
    for (int i = 0; i < size; i++) {
        fscanf(inputFile, "%d", &data[i]);
    }

    fclose(inputFile);

    /* Compute results */
    double avg = computeAverage(data, size);
    int max = computeMax(data, size);

    /* Print to screen */
    printf("Array Size: %d\n", size);
    printf("Average   : %.2f\n", avg);
    printf("Maximum   : %d\n", max);

    /* Write to file */
    outputFile = fopen("answer-hw3.txt", "w");

    if (outputFile == NULL) {
        printf("Error creating output file.\n");
        free(data);
        return 1;
    }

    fprintf(outputFile, "Array Size: %d\n", size);
    fprintf(outputFile, "Average   : %.2f\n", avg);
    fprintf(outputFile, "Maximum   : %d\n", max);

    fclose(outputFile);

    free(data);

    return 0;
}