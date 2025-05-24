/**
 * @file direct_dft.c
 * @author Brad Saylor
 * @brief Compute DFT via direct method
 * @version 0.1
 * @date 2025-05-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/direct_dft.h"

#include <complex.h>
#include <math.h>

int direct_dft(double complex *signal, double complex *signal_out, int N) {
  for (int k = 0; k < N; k++) {
    for (int n = 0; n < N; n++) {
      signal_out[k] += signal[n] * cexp(-2 * PI * I * k * n / N);
    }
  }

  return 0;
}
