#include "../include/window.h"
#include "../include/logs.h"

#include <math.h>
#include <stdio.h>

/**
 * @brief Applies Hanning window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_hanning(double complex* signal, size_t signal_length);

/**
 * @brief Applies Hamming window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_hamming(double complex* signal, size_t signal_length);

/**
 * @brief Applies Kaiser window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @param beta User supplied window parameter
 * @return int
 */
int window_kaiser(double complex* signal, size_t signal_length, double beta);

/**
 * @brief Applies Blackman-Harris window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_blackman_harris(double complex* signal, size_t signal_length);

/**
 * @brief Applies flat top window
 *
 * @param signal Signal to be windowed
 * @param signal_length Number of samples in signal
 * @return int
 */
int window_flat_top(double complex* signal, size_t signal_length);

/**
 * @brief Utility function for implementing types of raised cosine window
 *
 * @param signal Signal to be windowed
 * @param signal_length  Number of samples in signal
 * @param param1 Raised cosine constant parameter
 * @param param2 Raised cosine sinusoid parameter
 * @return int
 */
int window_raised_cosine(double complex* signal, size_t signal_length,
                         double* coeffs);

/**
 * @brief Calculate modified Bessel function of the first kind
 * for kaiser windowing
 *
 * @param x discrete signal index
 * @return int
 */
int bessel_I0(double x);

int window(double complex* signal, size_t signal_length, windowMode window_mode,
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
    case WINDOW_FLAT_TOP:
      window_flat_top(signal, signal_length);
      break;
    default:
      printf("Invalid window type\n");
      return 1;
  }
  log_out(LOG_INFO, "Window applied successfully.");
  return 0;
}

int window_hanning(double complex* signal, size_t signal_length) {
  log_out(LOG_INFO, "Applying Hanning window.");
  double raised_cosine_coeffs[5] = {0.5, -0.5, 0, 0, 0};
  window_raised_cosine(signal, signal_length, raised_cosine_coeffs);
  return 0;
}

int window_hamming(double complex* signal, size_t signal_length) {
  log_out(LOG_INFO, "Applying Hamming window.");
  double raised_cosine_coeffs[5] = {0.54, -0.46, 0, 0, 0};
  window_raised_cosine(signal, signal_length, raised_cosine_coeffs);
  return 0;
}

int window_blackman_harris(double complex* signal, size_t signal_length) {
  log_out(LOG_INFO, "Applying Blackman-Harris window");
  double raised_cosine_coeffs[5] = {0.35875, -0.48829, 0.14128, -0.01168, 0};
  window_raised_cosine(signal, signal_length, raised_cosine_coeffs);
  return 0;
}

int window_flat_top(double complex* signal, size_t signal_length) {
  log_out(LOG_INFO, "Applying flat top window.");
  double raised_cosine_coeffs[5] = {0.21557895, -.41663158, 0.277263158,
                                    -.083578947, 0.006947368};
  window_raised_cosine(signal, signal_length, raised_cosine_coeffs);
  return 0;
}

int window_raised_cosine(double complex* signal, size_t signal_length,
                         double* coeffs) {
  for (int i = 0; i < signal_length; i++) {
    double sum = 0;
    for (int j = 0; j < 5; j++) {
      sum += coeffs[j] * cos(2 * j * PI * i / signal_length);
    }
    signal[i] *= sum;
  }
  return 0;
};

int window_kaiser(double complex* signal, size_t signal_length, double beta) {
  log_out(LOG_INFO, "Applying Kaiser window.");
  // If no beta requested set value to 8.6 for ~100dB side lobe attenuation
  if (beta == 0) {
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
