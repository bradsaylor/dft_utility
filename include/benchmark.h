#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <complex.h>

#include "dft.h"

typedef struct {
  double mean;
  double min;
  double max;
  double std_dev;
} benchmarkResults;

int benchmark(algorithmMode alg_mode, size_t output_length, size_t input_length,
              double complex *input_signal, double complex **output_signal,
              size_t num_iter, benchmarkResults *benchmark_results);

#endif  // !BENCHMARK_H
