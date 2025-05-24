#ifndef READ_SEQUENCE_H
#define READ_SEQUENCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "complex.h"

/**
 * @brief Reads a complex discrete-time signal from a file.
 * @param filename Name of data file.
 * @param max_len User defined maximum sequence length.
 * @param len User provided int* to store length returned.
 * @warning The caller is responsible for freeing the allocated memory.
 */

double complex *read_sequence(const char *filename, int max_len, int *len);

#ifdef __cplusplus
}
#endif

#endif  // READ_SEQUENCE_H
