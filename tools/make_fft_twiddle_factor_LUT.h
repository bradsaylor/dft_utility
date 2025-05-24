#ifndef MAKE_FFT_TWIDDLE_FACTOR_LUT_H
#define MAKE_FFT_TWIDDLE_FACTOR_LUT_H

/**
 * @brief Define PI
 * 
 */
#ifndef PI
#define PI 3.14159265358979323846
#endif

/**
 * @brief Max power of two for lookup table
 * 
 */
const int MAX_POWER = 20;

/**
 * @brief Number of elements per line in lookup table
 * 
 */
const int NUM_PER_LINE = 10;

/**
 * @brief Name of lookup table c header file
 * 
 */
const char header_file_name[] = "fft_twiddle_factor_LUT.h";

/**
 * @brief Name of luukup table c source file
 * 
 */
char source_file_name[] = "fft_twiddle_factor_LUT.c";



#endif  // MAKE_FFT_TWIDDLE_FACTOR_LUT_H