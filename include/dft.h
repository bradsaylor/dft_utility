#ifndef DFT_H
#define DFT_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Struct holding program config parameters
 *
 */
typedef struct {
  const size_t MAX_INPUT;
  const char* output_dir;
} ProgramConfig;

/**
 * @brief Algorithm mode enumerations
 *
 */
typedef enum {
  ALG_MODE_UNKNOWN,
  ALG_MODE_DIRECT,
  ALG_MODE_FFT,
  ALG_MODE_IFFT,
  ALG_MODE_GOERTZEL,
} algorithmMode;

/**
 * @brief Output mode enumerations
 *
 */
typedef enum { OUTPUT_UNKNOWN, OUTPUT_TXT, OUTPUT_CSV, OUTPUT_BIN } outputMode;

/**
 * @brief Window mode enumerations
 *
 */
typedef enum {
  WINDOW_UNKNOWN,
  WINDOW_HANNING,
  WINDOW_HAMMING,
  WINDOW_KAISER,
  WINDOW_BLACKMAN_HARRIS,
  WINDOW_FLAT_TOP,
} windowMode;

/**
 * @brief Struct to hold options entered from cli
 *
 */
typedef struct {
  char input_file_name[50];
  char output_file_name[50];
  algorithmMode algorithm_mode;
  outputMode output_mode;
  windowMode window_mode;
  double window_param;
  int output_source;
  double sampling_freq;
  int write_meta;
  size_t requested_length;
  int truncate_ok;
  int run_benchmark;
  size_t benchmark_iterations;
} CliConfiguration;

#endif  // DFT_H
