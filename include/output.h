#ifndef OUTPUT_H
#define OUTPUT_H

#include <complex.h>

#include "dft.h"

int write_output_file(char *output_filename, const char *output_dir, outputMode output_mode,
                      double complex *output_sequence, int output_length);
int write_CSV(char *output_filename, const char *output_dir, double complex *output_sequence,
              int output_length);
int write_TXT(char *output_filename, const char *output_dir, double complex *output_sequence,
              int output_length);
int write_BIN(char *output_filename, const char *output_dir, double complex *output_sequence,
              int output_length);

#endif  // OUTPUT_H