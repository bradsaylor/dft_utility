#ifndef GTZL_DFT_H
#define GTZL_DFT_H

#include <complex.h>

/**
 * @brief Computes the Discrete Fourier Transform via the Goertzel Algorithm.
 * @param signal Input sequence.
 * @param signal_out Output sequence.
 * @param N Number of samples.
 */
int gtzl_dft(double complex* signal, double complex* signal_out, int N);

#ifndef PI
#define PI 3.14159265358979323846
#endif

#endif  // GTZL_DFT_H