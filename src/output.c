#include "../include/output.h"

#include <stdio.h>
#include <string.h>

int write_output_file(char *output_filename, const char *output_dir,
                      outputMode output_mode, double complex *output_sequence,
                      int output_length) {
  switch (output_mode) {
    case (OUTPUT_CSV):
      if(write_CSV(output_filename, output_dir, output_sequence, output_length)){
        printf("Could not write output CSV file.\n");
        return -1;
      }
      break;
    case (OUTPUT_TXT):
      if(write_TXT(output_filename, output_dir, output_sequence, output_length)){
        printf("Could not write output TXT file.\n");
        return -1;
      }
      break;
    case (OUTPUT_BIN):
      if(write_BIN(output_filename, output_dir, output_sequence, output_length)){
        printf("Could not write output BIN file.\n");
        return -1;
      }
      break;
    default:
      break;
  }
  return 0;
}

int write_CSV(char *output_filename, const char *output_dir,
              double complex *output_sequence, int output_length) {
  char output_path[50] = {0};
  strcat(output_path, output_dir);
  strcat(output_path, output_filename);
  FILE *fp = fopen(output_path, "w");
  if (!fp) {
    printf("\nError: Unable to write output file\n");
    return -1;
  }
  fprintf(fp, "index,real,imag\n");
  for (int i = 0; i < output_length; i++) {
    fprintf(fp, "%d,%lf,%lf\n", i, creal(output_sequence[i]),
            cimag(output_sequence[i]));
  }
  fclose(fp);
  return 0;
}

int write_TXT(char *output_filename, const char *output_dir,
              double complex *output_sequence, int output_length) {
  char output_path[50] = {0};
  strcat(output_path, output_dir);
  strcat(output_path, output_filename);
  FILE *fp = fopen(output_path, "w");
  if (!fp) {
    printf("\nError: Unable to write output file\n");
    return -1;
  }

  for (int i = 0; i < output_length; i++) {
    fprintf(fp, "%.2lf + %.2lfi\n", creal(output_sequence[i]),
            cimag(output_sequence[i]));
  }
  fclose(fp);
  return 0;
}

int write_BIN(char *output_filename, const char *output_dir,
              double complex *output_sequence, int output_length) {
  char output_path[50] = {0};
  strcat(output_path, output_dir);
  strcat(output_path, output_filename);
  FILE *fp = fopen(output_path, "wb");
  if (!fp) {
    printf("\nError: Unable to write output file\n");
    return -1;
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