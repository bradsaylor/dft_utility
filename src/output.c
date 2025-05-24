#include "../include/output.h"

#include <stdio.h>
#include <string.h>

int write_output_file(char *output_filename, outputMode output_mode,
                      double complex *output_sequence, int output_length) {
  
  switch (output_mode) {
    case (OUTPUT_CSV):
      write_CSV(output_filename, output_sequence, output_length);
      break;
    case (OUTPUT_TXT):
      write_TXT(output_filename, output_sequence, output_length);
      break;
    case (OUTPUT_BIN):
      write_BIN(output_filename, output_sequence, output_length);
      break;
    default:
      break;
  }
  return 0;
}

int write_CSV(char *output_filename, double complex *output_sequence,
              int output_length) {
  FILE *fp = fopen(output_filename, "w");
  if (!fp) {
    printf("\nError: Unable to write output file\n");
  }
  fprintf(fp, "index,real,imag\n");
  for (int i = 0; i < output_length; i++) {
    fprintf(fp, "%d,%lf,%lf\n", i, creal(output_sequence[i]),
            cimag(output_sequence[i]));
  }
  fclose(fp);
  return 0;
}

int write_TXT(char *output_filename, double complex *output_sequence,
              int output_length) {
  FILE *fp = fopen(output_filename, "w");
  if (!fp) {
    printf("\nError: Unable to write output file\n");
  }

  for (int i = 0; i < output_length; i++) {
    fprintf(fp, "%.2lf + %.2lfi\n", creal(output_sequence[i]),
            cimag(output_sequence[i]));
  }
  fclose(fp);
  return 0;
}

int write_BIN(char *output_filename, double complex *output_sequence,
              int output_length) {
  FILE *fp = fopen(output_filename, "wb");
  if (!fp) {
    printf("\nError: Unable to write output file\n");
  }
  for (int i = 0; i < output_length; i++) {
    double re = creal(output_sequence[i]);
    double im = cimag(output_sequence[i]);
    fwrite(&re, sizeof(double), 1, fp);
    fwrite(&im, sizeof(double), 1, fp);
  }
  fclose(fp);
  return 0;
}