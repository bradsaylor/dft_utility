#ifndef WINDOW_H
#define WINDOW_H

#include <complex.h>
#include <stddef.h>

#include "../include/cli.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif

/**
 * @brief Distributes signal to applicable windowing function
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @param window_mode Requested windowing mode
 * @return int
 */

/**
 * @brief
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @param window_mode Requested windowing mode
 * @param window_param User supplied windowing parameter
 * @return int
 */
int window(double complex *signal, size_t signal_length, windowMode window_mode,
           double window_param);

/**
 * @brief Applies Hanning window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_hanning(double complex *signal, size_t signal_length);

/**
 * @brief Applies Hamming window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_hamming(double complex *signal, size_t signal_length);

/**
 * @brief Applies Kaiser window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @param beta User supplied window parameter
 * @return int
 */
int window_kaiser(double complex *signal, size_t signal_length, double beta);

/**
 * @brief Applies Blackman-Harris window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_blackman_harris(double complex *signal, size_t signal_length);

/**
 * @brief Applies flat top window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_flat_top(double complex *signal, size_t signal_length);

/**
 * @brief Utility function for implementing types of raised cosine window
 *
 * @param signal Signal to be windowed
 * @param signal_length  Number of samples in signal
 * @param param1 Raised cosine constant parameter
 * @param param2 Raised cosine sinusoid parameter
 * @return int
 */
int window_raised_cosine(double complex *signal, size_t signal_length,
                         double *coeffs);

/**
 * @brief Calculate modified Bessel function of the first kind
 * for kaiser windowing
 *
 * @param x discrete signal index
 * @return int
 */
int bessel_I0(double x);

#endif  // WINDOW_H