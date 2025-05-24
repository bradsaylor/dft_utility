#include "make_fft_twiddle_factor_LUT.h"

#include <complex.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <output.c> <outout.h>\n", argv[0]);
    return 1;
  }

  const char *source_file_path = argv[1];
  const char *header_file_path = argv[2];

  FILE *fp = fopen(header_file_path, "w");
  if (!fp) {
    perror("fopen header failed");
    return 1;
  }

  // Header formatting
  fprintf(fp, "#ifndef FFT_TWIDDLE_FACTOR_LUT_H\n");
  fprintf(fp, "#define FFT_TWIDDLE_FACTOR_LUT_H\n");
  fprintf(fp, "#include <complex.h>\n\n");
  fprintf(fp, "extern const double complex *twiddle_factor_LUT[%d];\n\n",
          MAX_POWER);
  fprintf(fp, "#endif // FFT_TWIDDLE_FACTOR_LUT_H");
  fclose(fp);

  fp = fopen(source_file_path, "w");
  if (!fp) {
    perror("fopen source failed\n");
    return 1;
  }

  fprintf(fp, "#include \"../include/fft_twiddle_factor_LUT.h\"\n");
  fprintf(fp, "#include <complex.h>\n\n");

  fprintf(fp, "const double complex *twiddle_factor_LUT[%d] = {\n", MAX_POWER);

  for (int count = 0; count < MAX_POWER; count++) {
    fprintf(fp, "(double complex[]){\n\t");
    int print_count = 0;
    double complex WN = cexp(-2 * PI * I / pow(2, count));

    // Handle zero case, never used but necessary for indexing
    if (count == 0) {
      fprintf(fp, "\t0 + 0*I");
    }

    // Print next element
    for (int i = 0; i < (int)(pow(2, count) / 2); i++) {
      fprintf(fp, "\t%lf + %lf*I,", creal(cpow(WN, i)), cimag(cpow(WN, i)));
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