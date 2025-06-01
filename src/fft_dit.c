/**
 * @file fft_dit.c
 * @author Brad Saylor
 * @brief Calculates DFT via FFT time decimation algorithm
 * @version 0.1
 * @date 2025-05-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/fft_dit.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../tools/generated/include/fft_reverse_index_LUT.h"
#include "../tools/generated/include/fft_twiddle_factor_LUT.h"

int fft_dit(double complex *signal, double complex *signal_out, int N) {
  int num_decims = (int)log2(N);  // Total number of decimation steps

  // Copy signal to output sequence in reversed bit order
  for (int i = 0; i < N; i++) {
    signal_out[i] = signal[(int)reverse_index_LUT[num_decims][i]];
  }

  // Perform each decimation step
  for (int i = 0; i < num_decims; i++) {
    calc_decimation_step(signal_out, num_decims, i + 1, N);
  }
  return 0;
}

int calc_decimation_step(double complex *sequence, int num_decims,
                         int decim_step, int N) {
  // Length of each decimated DFT
  int decim_DFT_length = pow(2, decim_step);
  int half_decim_DFT_length = (int)(decim_DFT_length / 2);

  int num_decim_DFTs =
      (int)(N / decim_DFT_length);    // number of decimated DFT's
  int WN_step_size = num_decim_DFTs;  // twiddle factor index increment
  int btrfly_bottom_index = 0;        // indicies for butterfly calc
  int btrfly_top_index = 0;

  // Loop over total number of decimated DFT's
  for (int i = 0; i < num_decim_DFTs; i++) {
    int WN_index = 0;  // twiddle factor index

    // Loop over pairs of indices inside decimated DFT
    for (int j = 0; j < half_decim_DFT_length; j++) {
      btrfly_top_index = i * decim_DFT_length + j;
      btrfly_bottom_index = i * decim_DFT_length + half_decim_DFT_length + j;

      // Calculate butterfly for this pair of indices in place
      calc_butterfly(&sequence[btrfly_top_index],
                     &sequence[btrfly_bottom_index], num_decims, WN_index);
      WN_index += WN_step_size;
    }
  }
  return 0;
}

int calc_butterfly(double complex *btrfly_top_element,
                   double complex *btrfly_bottom_element, int num_decims,
                   int WN_index) {
  // Twiddle factor for this butterfuly, from lookup table
  double complex WN = twiddle_factor_LUT[num_decims][WN_index];

  // Perform twiddle factor mult. on bottom element
  double complex new_bottom = WN * *btrfly_bottom_element;

  // Write new values in place
  *btrfly_bottom_element = *btrfly_top_element - new_bottom;
  *btrfly_top_element = *btrfly_top_element + new_bottom;

  return 0;
}
