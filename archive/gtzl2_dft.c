#include "../include/gtzl_dft.h"

#include <complex.h>
#include <math.h>

int gtzl2_dft(double complex *signal, double complex *signal_out, int N) {
    int half_N = N / 2;

    for (int k = 0; k <= half_N; ++k) {
    double omega = 2.0 * PI * k / N;
    double complex Wk = cexp(-I * omega);
    double complex WNk = cexp(-I * 2.0 * PI * (N - k) / N);  // projection for N-k
    double complex pole_const = 2.0 * cos(omega);

    // shared recurrence
    double complex s = 0;
    double complex s_prev1 = 0;
    double complex s_prev2 = 0;

    for (int n = 0; n < N; ++n) {
      s = signal[n] + pole_const * s_prev1 - s_prev2;
      s_prev2 = s_prev1;
      s_prev1 = s;
    }

    // projection for bin k
    signal_out[k] = s - Wk * s_prev2;

    // projection for bin N - k (only if not self-conjugate)
    if (k != 0 && !(N % 2 == 0 && k == half_N)) {
      signal_out[N - k] = s - WNk * s_prev2;
    }
  }

  return 0;
}
