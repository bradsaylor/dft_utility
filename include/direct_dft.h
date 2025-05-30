#ifndef DIRECT_FFT_H
#define DIRECT_FFT_H

#include <complex.h>

/**
 * @brief Computes the Discrete Fourier Transform (DFT) Directly.
 * @param signal Input sequence.
 * @param signal_out Output sequence.
 * @param N Number of samples.
 */
int direct_dft(double complex *signal, double complex *signal_out, int N);

#ifndef PI
#define PI 3.14159265358979323846
#endif

#endif  // DIRECT_FFT_H