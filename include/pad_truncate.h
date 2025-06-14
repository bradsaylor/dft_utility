#ifndef PAD_TRUNCATE_H
#define PAD_TRUNCATE_H

#include <complex.h>
#include <stddef.h>

int pad_and_truncate(double complex** input_signal, size_t requested_length,
                     size_t input_length);

#endif  // PAD_TRUNCATE_H