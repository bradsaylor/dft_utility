#ifndef IFFT_DIT_H
#define IFFT_DIT_H

#include <complex.h>

/**
 * @brief Calculates iDFT via FFT decimation in time algorithm
 *
 * @param signal Input signal
 * @param signal_out Output signal
 * @param N Size of output sequence
 * @return int
 */
int ifft_dit(double complex *signal, double complex *signal_out, int N_in,
             int N_out);

/**
 * @brief Return conjugate of signal
 * 
 * @param signal Input signal
 * @param N Size of input signal
 * @return int 
 */
int conjugate_signal(double complex *signal, int N);

#endif  // IFFT_DIT_H
