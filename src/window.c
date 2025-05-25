#include "../include/window.h"

#include <math.h>
#include <stdio.h>

int window(double complex *signal, int signal_length, windowMode window_mode,
           double window_param) {
  switch (window_mode) {
    case WINDOW_HANNING:
      window_hanning(signal, signal_length);
      break;
    case WINDOW_HAMMING:
      window_hamming(signal, signal_length);
      break;
    case WINDOW_KAISER:
      window_kaiser(signal, signal_length, window_param);
      break;
    case WINDOW_BLACKMAN_HARRIS:
      window_blackman_harris(signal, signal_length);
      break;
    default:
      printf("Invalid window type\n");
      return 1;
  }
}

int window_hanning(double complex *signal, int signal_length) {
  double raised_cosine_coeffs[5] = {0.5, -0.5, 0, 0, 0};
  window_raised_cosine(signal, signal_length, raised_cosine_coeffs);
  return 0;
}

int window_hamming(double complex *signal, int signal_length) {
  double raised_cosine_coeffs[5] = {0.54, -0.46, 0, 0, 0};
  window_raised_cosine(signal, signal_length, raised_cosine_coeffs);
  return 0;
}

int window_blackman_harris(double complex *signal, int signal_length) {
  double raised_cosine_coeffs[5] = {0.35875, -0.48829, 0.14128, -0.01168, 0};
  window_raised_cosine(signal, signal_length, raised_cosine_coeffs);
  return 0;
}

int window_flat_top(double complex *signal, int signal_length) {
  double raised_cosine_coeffs[5] = {0.21557895, -.41663158, 0.277263158,
                                    -.083578947, 0.006947368};
  window_raised_cosine(signal, signal_length, raised_cosine_coeffs);
  return 0;
}

int window_raised_cosine(double complex *signal, int signal_length,
                         double *coeffs) {
  for (int i = 0; i < signal_length; i++) {
    double sum = 0;
    for (int j = 0; j < 5; j++) {
      sum += coeffs[j] * cos(2 * j * PI * i / signal_length);
    }
    signal[i] *= sum;
  }
  return 0;
};

int window_kaiser(double complex *signal, int signal_length, double beta) {
  // If no beta requested set value to 8.6 for ~100dB side lobe attenuation
  if(beta == 0){
    beta = 8.6;
    printf("No window parameter specified, using beta=8.6\n");
  }
  double denom = bessel_I0(beta);

  for (int i = 0; i < signal_length; i++) {
    double r = 2.0 * i / (signal_length - 1.0) - 1.0;
    double x = beta * sqrt(1.0 - r * r);
    signal[i] *= bessel_I0(x) / denom;
  }
  return 0;
}

int bessel_I0(double x) {
  double result = 1.0;
  double this_iter = 1.0;
  double const_term = x * x / 4.0;
  int k = 1;

  while (this_iter > 1e-10 * result) {
    this_iter *= const_term / (k * k);
    result += this_iter;
    k++;
  }

  return result;
}