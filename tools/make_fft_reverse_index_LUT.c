/**
 * @file make_fft_dit_lut.c
 * @author Brad Saylor
 * @brief Creates C header file lookup table of bit reversed indexes for fft
 * algorithm
 * @version 0.1
 * @date 2025-05-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "make_fft_reverse_index_LUT.h"

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

uint32_t bit_reverse(uint32_t num, int N) {
  uint32_t rev_num = 0;

  // Loop over all N bits
  for (int i = 0; i < N; i++) {
    // If bit i holds a one rev_num bit (N-1-i) is 1
    if ((uint32_t)1 << i & num) {
      rev_num |= ((uint32_t)1 << (N - 1 - i));
    }
  }

  return rev_num;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s output.c output.h\n", argv[0]);
    return 1;
  }

  const char *source_file_path = argv[1];
  const char *header_file_path = argv[2];

  // Write header file
  FILE *fp = fopen(header_file_path, "w");
  if (!fp) {
    perror("fopen header");
    return 1;
  }

  // Header formatting
  fprintf(fp, "#ifndef FFT_DIT_LUT_H\n");
  fprintf(fp, "#define FFT_DIT_LUT_H\n");
  fprintf(fp, "#include <stdint.h>\n\n");
  // Declare LUT as extern
  fprintf(fp, "extern const uint32_t *reverse_index_LUT[%d];\n\n", pow2);
  // Close off header formatting
  fprintf(fp, "#endif //FFT_DIT_LUT");
  fclose(fp);

  // Write source file
  fp = fopen(source_file_path, "w");
  if (!fp) {
    perror("fopen source");
    return 1;
  }

  fprintf(fp, "#include \"../include/fft_reverse_index_LUT.h\"\n\n");

  // Declare pointer array and generate one array
  // per power of 2 using bit reverse function
  fprintf(fp, "const uint32_t *reverse_index_LUT[%d] = {\n", pow2);

  for (int count = 0; count < pow2; count++) {
    fprintf(fp, "(uint32_t[]){\n\t");
    int print_count = 0;

    // Print next element
    for (uint32_t i = 0; i < (1U << count); i++) {
      fprintf(fp, "\t%u,", bit_reverse(i, count));
      print_count++;

      // If a newline is needed
      if (print_count == NUM_PER_LINE) {
        fprintf(fp, "\n\t");
        print_count = 0;
      }
    }
    fprintf(fp, "},\n");
  }
  fprintf(fp, "};\n");

  fclose(fp);

  return 0;
}
