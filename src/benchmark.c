#include "../include/benchmark.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/algorithms.h"
#include "../include/logs.h"

#define NS_PER_SEC 1000000000ULL
size_t warmup_iter = 10;

int calc_stats(uint64_t* results_array, benchmarkResults* benchmark_results,
               size_t num_iter);

int benchmark(algorithmMode alg_mode, size_t output_length, size_t input_length,
              double complex* input_signal, double complex** output_signal,
              size_t num_iter, benchmarkResults* benchmark_results) {
  if (num_iter == 0) {
    num_iter = 100;
    printf("Number of benchmark iterations set to default value, n=%lu.\n",
           num_iter);
    printf("Set iteration number with --benchmark-iterations [x] option\n");
  }
  log_out(LOG_INFO, "Running bench mark with n=%d iterations.", num_iter);
  uint64_t* results_array = calloc(num_iter, sizeof(uint64_t));
  if (!results_array) {
    printf("Could not calloc results array for benchmarking.\n");
    return -1;
  }
  struct timespec start = {0};
  struct timespec end = {0};

  // Perform warmup calls
  for (size_t i = 0; i < warmup_iter; i++) {
    dft_algorithms(alg_mode, output_length, input_length, input_signal,
                   output_signal);
  }

  // Perform benchmark calls
  for (size_t i = 0; i < num_iter; i++) {
    clock_gettime(CLOCK_MONOTONIC, &start);

    dft_algorithms(alg_mode, output_length, input_length, input_signal,
                   output_signal);

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Explicitly use 64bit type for 1E9
    results_array[i] =
      (end.tv_sec - start.tv_sec) * NS_PER_SEC + (end.tv_nsec - start.tv_nsec);
  }
  calc_stats(results_array, benchmark_results, num_iter);

  free(results_array);

  log_out(LOG_INFO, "Benchmark compelte.");
  return 0;
}

int calc_stats(uint64_t* results_array, benchmarkResults* benchmark_results,
               size_t num_iter) {
  double mean = 0;
  double std_dev = 0;
  uint64_t sum = 0;
  double var_sum = 0;
  uint64_t min = results_array[0];
  uint64_t max = results_array[0];

  for (size_t i = 0; i < num_iter; i++) {
    if (results_array[i] > max)
      max = results_array[i];
    else if (results_array[i] < min)
      min = results_array[i];
    sum += results_array[i];
  }

  mean = (double)sum / (num_iter);

  double diff = 0;
  for (size_t i = 0; i < num_iter; i++) {
    diff = (double)results_array[i] - mean;
    var_sum += (diff * diff);
  }
  std_dev = sqrt((double)var_sum / (num_iter - 1));

  benchmark_results->num_iter = num_iter;
  benchmark_results->max = max;
  benchmark_results->min = min;
  benchmark_results->mean = mean;
  benchmark_results->std_dev = std_dev;
  return 0;
}
