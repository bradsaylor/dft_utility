/**
 * @file read_sequence.c
 * @author Brad Saylor
 * @brief Read discrete signal from file
 * @version 0.1
 * @date 2025-05-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../include/read_sequence.h"
#include <stdio.h>
#include <stdlib.h>

double complex* read_sequence(const char *filename, int max_len, int *len) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    int count = 0;
    double re = 0;
    double im = 0;
    while (fscanf(file, "%lf%lfj", &re, &im) == 2) {
        count++;
    }

    if (count > max_len) {
        fprintf(stderr, "File contains more than %d elements\n", max_len);
        fclose(file);
        return NULL;
    }

    rewind(file);

    double complex *x = calloc(count, sizeof(double complex));
    if (!x) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < count; ++i) {
        if (fscanf(file, "%lf%lfj", &re, &im) != 2) {
            fprintf(stderr, "Error reading complex element %d\n", i);
            free(x);
            fclose(file);
            return NULL;
        }
        x[i] = re + im * I;
    }

    fclose(file);
    *len = count;
    return x;
}
