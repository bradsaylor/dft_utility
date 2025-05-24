#ifndef FFT_DIT_H
#define FFT_DIT_H

#include <complex.h>

/**
 * @brief Calculates DFT via FFT decimation in time algorithm
 *
 * @param signal
 * @param signal_out
 * @param N
 * @return int
 */
int fft_dit(double complex *signal, double complex *signal_out, int N);

/**
 * @brief Calculates one decimation step of FFT algorithm
 *
 * @param sequence Intermediate data sequence
 * @param num_decims Total number of decimation steps
 * @param decim_step Current decimation step
 * @param N Size of output sequence
 * @return int
 */
int calc_decimation_step(double complex *sequence, int num_decims,
                         int decim_step, int N);

/**
 * @brief Calculates single butterfly step of FFT algorithm
 *
 * @param btrfly_top_element Top half element of butterfly
 * @param btrfly_bottom_element Bottom half element of butterfly
 * @param num_decims Total number of decimation steps
 * @param WN_index Lookup index for twiddle factor
 * @return int
 */
int calc_butterfly(double complex *btrfly_top_element,
                   double complex *btrfly_bottom_element, int num_decims,
                   int WN_index);

#endif  // FFT_DIT_H