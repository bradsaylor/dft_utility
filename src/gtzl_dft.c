/**
 * @file gtzl_dft.c
 * @author Brad Saylor
 * @brief Compute DFT via Goertzel Algorithm
 * @version 0.1
 * @date 2025-05-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/gtzl_dft.h"

#include <complex.h>
#include <math.h>

int gtzl_dft(double complex *signal, double complex *signal_out, int N) {
  for (int k = 0; k < (N / 2 + 1); k++) {
    double complex s = 0;   // current state of recursion
    double complex s1 = 0;  // previous state of recursion
    double complex s2 = 0;  // previous previous state of recursion
    double complex sN = 0;

    // Multipliers only need to be computed once per k
    double complex Wk = cexp(-I * 2 * PI * k / N);
    double complex pole_const = 2 * cos(2 * PI * k / N);

    // loop over n tracking the current and previous internal ss
    for (int n = 0; n < N; n++) {
      s2 = s1;
      s1 = s;
      s = signal[n] + pole_const * s1 - s2;
    }
    // complex zero contribution calculated after n summation
    // is complete
    sN = pole_const * s - s1;
    signal_out[k] = sN - Wk * s;

    // also write out value for N-k if exp(jk/N) is not
    // it's own conjugate
    int self_conjugate = (k == 0) || (N % 2 == 0 && k == N / 2);
    if (!self_conjugate) {
      signal_out[N - k] = sN - conj(Wk) * s;
    }
  }

  return 0;
}