#include "../include/window.h"

#include <math.h>
#include <stdio.h>

int window(double complex *signal, int signal_length, windowMode window_mode) {
  switch (window_mode) {
    case WINDOW_HANNING:
      window_hanning(signal, signal_length);
      break;
    case WINDOW_HAMMING:
      window_hamming(signal, signal_length);
      break;
    case WINDOW_KAISER:
      window_kaiser(signal, signal_length);
      break;
    case WINDOW_BLACKMAN_HARRIS:
      window_blackman_harris(signal, signal_length);
      break;
    default:
      printf("Invalid window type\n");
      return 1;
      break;
  }
}

int window_hanning(double complex *signal, int signal_length) {
  double const_param = 0.5;
  double sin_param = 0.5;
  window_raised_cosine(signal, signal_length, const_param, sin_param);
  return 0;
}

int window_hamming(double complex *signal, int signal_length) {
  double const_param = 0.54;
  double sin_param = 0.46;
  window_raised_cosine(signal, signal_length, const_param, sin_param);
  return 0;
}

int window_kaiser(double complex *signal, int signal_length) { return 0; }

int window_blackman_harris(double complex *signal, int signal_length) {
  for (int i = 0; i < signal_length; i++) {
    signal[i] = 0.42 - 0.5 * cos(2 * PI * i / signal_length) +
                0.08 * cos(4 * PI * i / signal_length);
  }
  return 0;
}
int window_raised_cosine(double complex *signal, int signal_length,
                          double param1, double param2) {
  for (int i = 0; i < signal_length; i++) {
    signal[i] = param1 - param2 * cos(2 * PI * i / signal_length);
  }
  return 0;
};