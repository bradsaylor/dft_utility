#ifndef CLI_H
#define CLI_H

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

typedef enum {
  WINDOW_UNKNOWN,
  WINDOW_HANNING,
  WINDOW_HAMMING,
  WINDOW_KAISER,
  WINDOW_BLACKMAN_HARRIS,
  WINDOW_FLAT_TOP,
} windowMode;

typedef struct {
  char input_file_name[50];
  char output_file_name[50];
  algorithmMode algorithm_mode;
  outputMode output_mode;
  windowMode window_mode;
  double window_param;
} Configuration;

/**
 * @brief Parse and error check command line arguments
 *
 * @param argc Number of input argument strings given
 * @param argv Array of input argument strings
 * @param config Program configuration structure
 * @return int 0 if successful 1 otherwise
 */
int parse_cli(int argc, char *argv[], Configuration *config);

/**
 * @brief Print command usage and option information
 *
 * @return int
 */
int print_usage_help();

#endif  // CLI_H