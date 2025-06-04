#ifndef MAKE_FFT_REVERSE_INDEX_H
#define MAKE_FFT_REVERSE_INDEX_H

#include <inttypes.h>

/**
 * @brief Number of array elements per line in lookup table.
 *
 */
#define NUM_PER_LINE 10

/**
 * @brief Name of output header file.
 *
 */
char header_file_name[] = "fft_reverse_index_LUT.h";

/**
 * @brief Name of output source file
 *
 */
char source_file_name[] = "fft_reverse_index_LUT.c";

/**
 * @brief Maximum power of 2 to be computed for lookup table
 *
 */
int pow2 = 20;

/**
 * @brief Reverses bit sequence of a number represented by N bits.
 *
 * @param num Number to be reversed as uint32_t
 * @param N Number of bits in binary number representation
 * @return The reversed representation as uint32_t
 */
uint32_t bit_reverse(uint32_t num, int N);


#endif  // MAKE_FFT_REVERSE_INDEX_H