#ifndef DFT_H
#define DFT_H

#include <complex.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "direct_dft.h"
#include "fft_dit.h"
#include "gtzl_dft.h"
#include "ifft_dit.h"
#include "output.h"
#include "read_sequencev2.h"
#include "window.h"
#include "algorithms.h"

const size_t MAX_INPUT = 1024;
const char *output_dir = "./output/";



#endif  // DFT_H
