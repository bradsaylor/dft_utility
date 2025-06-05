#include "../include/pad_truncate.h"

#include <stdio.h>
#include <stdlib.h>

int pad_signal(double complex **input_signal, size_t requested_length,
               size_t input_length);
int truncate_signal(double complex **input_signal, size_t requested_length);

int pad_and_truncate(double complex **input_signal, size_t requested_length,
                     size_t input_length) {
  if (input_length < requested_length) {
    if (pad_signal(input_signal, requested_length, input_length)) return 1;

  } else if (input_length > requested_length) {
    if (truncate_signal(input_signal, requested_length)) return 1;
  }

  return 0;
}

int pad_signal(double complex **input_signal, size_t requested_length,
               size_t input_length) {
  *input_signal =
      realloc(*input_signal, requested_length * sizeof(double complex));
  if (!(*input_signal)) {
    printf("Not able to zero-pad the input signal.\n");
    return -1;
  }
  for (int i = input_length; i < requested_length; i++) {
    (*input_signal)[i] = 0 + 0 * I;
  }
  return 0;
}

int truncate_signal(double complex **input_signal, size_t requested_length) {
  *input_signal =
      realloc(*input_signal, requested_length * sizeof(double complex));
  if (!(*input_signal)) {
    printf("Not able to truncate the input signal.\n");
    return -1;
  }
  return 0;
}