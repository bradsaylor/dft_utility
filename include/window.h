#ifndef WINDOW_H
#define WINDOW_H

#include <complex.h>

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
int window(double complex *signal, int signal_length, windowMode window_mode);

/**
 * @brief Applies Hanning window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_hanning(double complex *signal, int signal_length);

/**
 * @brief Applies Hamming window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_hamming(double complex *signal, int signal_length);

/**
 * @brief Applies Kaiser window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_kaiser(double complex *signal, int signal_length);

/**
 * @brief Apples Blackman-Harris window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_blackman_harris(double complex *signal, int signal_length);

/**
 * @brief Utility function for implementing types of raised cosine window
 * 
 * @param signal Signal to be windowed 
 * @param signal_length  Number of samples in signal
 * @param param1 Raised cosine constant parameter
 * @param param2 Raised cosine sinusoid parameter
 * @return int 
 */
int window_raised_cosine(double complex *signal, int signal_length, double param1, double param2);

#endif  // WINDOW_H