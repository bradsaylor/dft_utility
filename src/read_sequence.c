#include "../include/read_sequence.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/logs.h"

int read_complex_text(const char* filename, double complex** data_out,
                      size_t* len_out, const size_t MAX_INPUT);

int read_complex_csv(const char* filename, double complex** data_out,
                     size_t* len_out, const size_t MAX_INPUT);

int read_complex_bin(const char* filename, double complex** data_out,
                     size_t* len_out, const size_t MAX_INPUT);

int read_sequence(const char* filename, double complex** data_out,
                  size_t* len_out, const size_t MAX_INPUT) {
  const char* ext = strrchr(filename, '.');
  if (!ext) return -1;

  if (strcmp(ext, ".bin") == 0) {
    if (read_complex_bin(filename, data_out, len_out, MAX_INPUT)) {
      printf("Error reading BIN file.\n");
      return -1;
    }
  } else if (strcmp(ext, ".csv") == 0) {
    if (read_complex_csv(filename, data_out, len_out, MAX_INPUT)) {
      printf("Error reading CSV file.\n");
      return -1;
    }
  } else {
    if (read_complex_text(filename, data_out, len_out, MAX_INPUT)) {
      printf("Error reading TXT file\n");
      return -1;
    }
  }

  log_out(LOG_INFO, "Input file read successfully.");
  log_out(LOG_DEBUG, "Size of sequence: \n\tbytes:\t\t %zu \n\telements:\t %lu",
          *len_out * sizeof(double complex), len_out);
  return 0;
}

int read_complex_text(const char* filename, double complex** data_out,
                      size_t* len_out, const size_t MAX_INPUT) {
  log_out(LOG_INFO, "Reading %s.", filename);
  FILE* file = fopen(filename, "r");
  if (!file) return -1;

  size_t cap = 1024;
  size_t count = 0;
  double re, im;

  double complex* data = malloc(cap * sizeof(double complex));
  if (!data) return -1;

  while (fscanf(file, "%lf%lfj", &re, &im) == 2) {
    if (count == cap) {
      cap *= 2;
      double complex* temp = realloc(data, cap * sizeof(double complex));
      if (!temp) {
        free(data);
        fclose(file);
        return -1;
      }
      data = temp;
    }
    data[count++] = re + I * im;
    if (count > MAX_INPUT) {
      printf("Maxmim input file length exceeded\n");
      return -1;
    }
  }

  fclose(file);

  double complex* trimmed = realloc(data, count * sizeof(double complex));
  if (trimmed) data = trimmed;

  *data_out = data;
  *len_out = count;
  return 0;
}

int read_complex_csv(const char* filename, double complex** data_out,
                     size_t* len_out, const size_t MAX_INPUT) {
  log_out(LOG_INFO, "Reading %s.", filename);
  FILE* file = fopen(filename, "r");
  if (!file) return -1;

  size_t cap = 1024;
  size_t count = 0;
  double re, im;

  double complex* data = malloc(cap * sizeof(double complex));
  if (!data) {
    fclose(file);
    return -1;
  }

  while (fscanf(file, "%lf,%lf", &re, &im) == 2) {
    if (count == cap) {
      cap *= 2;
      double complex* temp = realloc(data, cap * sizeof(double complex));
      if (!temp) {
        free(data);
        fclose(file);
        return -1;
      }
      data = temp;
    }

    data[count++] = re + I * im;
    if (count > MAX_INPUT) {
      printf("Maxmim input file length exceeded\n");
      return -1;
    }
  }

  fclose(file);

  double complex* trimmed = realloc(data, count * sizeof(double complex));
  if (trimmed) data = trimmed;

  *data_out = data;
  *len_out = count;
  return 0;
}

int read_complex_bin(const char* filename, double complex** data_out,
                     size_t* len_out, const size_t MAX_INPUT) {
  log_out(LOG_INFO, "Reading %s.", filename);
  FILE* file = fopen(filename, "rb");
  if (!file) return -1;

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  if (file_size < 0) {
    fclose(file);
    return -1;
  }
  rewind(file);

  size_t count = file_size / sizeof(double complex);
  if (count > MAX_INPUT) {
    printf("Maxmim input file length exceeded\n");
    return -1;
  }

  double complex* data = malloc(count * sizeof(double complex));
  if (!data) {
    fclose(file);
    return -1;
  }

  size_t read = fread(data, sizeof(double complex), count, file);
  fclose(file);

  if (read != count) {
    free(data);
    return -1;
  }

  *data_out = data;
  *len_out = count;
  return 0;
}
