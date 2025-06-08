/**
 * @file ifft_dit.c
 * @author Brad Saylor
 * @brief Compute inverse FFT by using forward FFT decimation
 * in time algorithm
 * @version 0.1
 * @date 2025-05-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/ifft_dit.h"

#include <complex.h>

#include "../include/fft_dit.h"
#include "../include/logs.h"

int ifft_dit(double complex *signal, double complex *signal_out,
             size_t output_length) {
  log_out(LOG_INFO, "Applying inverse FFT algorithm.");
  conjugate_signal(signal, output_length);
  fft_dit(signal, signal_out, output_length);
  conjugate_signal(signal_out, output_length);
  log_out(LOG_INFO, "Applied inverse FFT algorithm successfully.");
  return 0;
}

int conjugate_signal(double complex *signal, size_t N) {
  log_out(LOG_INFO, "Conjugating the signal.");
  for (int i = 0; i < N; i++) {
    signal[i] = conj(signal[i]);
  }
  log_out(LOG_INFO, "Conjugated the signal successfully.");
  return 0;
}
