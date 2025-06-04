#ifndef IFFT_DIT_H
#define IFFT_DIT_H

#include <complex.h>
#include <stddef.h>

/**
 * @brief Calculates iDFT via FFT decimation in time algorithm
 *
 * @param signal Input signal
 * @param signal_out Output signal
 * @param N Size of output sequence
 * @return int
 */
int ifft_dit(double complex *signal, double complex *signal_out, size_t output_length);

/**
 * @brief Return conjugate of signal
 *
 * @param signal Input signal
 * @param N Size of input signal
 * @return int
 */
int conjugate_signal(double complex *signal, size_t N);

#endif  // IFFT_DIT_H
