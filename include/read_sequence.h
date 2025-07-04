#ifndef READ_SEQUENCEV2_H
#define READ_SEQUENCEV2_H

#include <complex.h>
#include <stddef.h>

int read_sequence(const char* filename, double complex** data_out,
                  size_t* len_out, const size_t MAX_INPUT);

#endif