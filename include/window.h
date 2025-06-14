#ifndef WINDOW_H
#define WINDOW_H

#include <complex.h>
#include <stddef.h>

#include "dft.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif

/**
 * @brief
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @param window_mode Requested windowing mode
 * @param window_param User supplied windowing parameter
 * @return int
 */
int window(double complex* signal, size_t signal_length, windowMode window_mode,
           double window_param);

#endif  // WINDOW_H