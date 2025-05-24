#include "../include/gtzl3_dft.h"

#include <complex.h>
#include <math.h>

int gtzl3_dft(double complex *signal, double complex *signal_out, int N) {
  for (int k = 0; k < N; k++) {
    double complex s = 0;
    double complex s1 = 0; 
    double complex s2 = 0;
    double complex sN = 0;
    double complex WN = cexp(-1 * I * 2 * PI * k / N);
    double cos_fact = 2 * cos(2 * PI * k / N);

    for (int n = 0; n < N; n++) {
      s2 = s1;
      s1 = s;
      s = signal[n] + cos_fact * s1 - s2;
    }

    sN = cos_fact * s - s1;
    signal_out[k] = sN - WN * s;
  }
}