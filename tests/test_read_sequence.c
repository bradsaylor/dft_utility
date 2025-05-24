#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <assert.h>

#include "../include/read_sequence.h"

void test_read_sequence_valid() {
    int len;
    double complex *x = read_sequence("tests/test_data/good_input.txt", 10, &len);
    assert(x != NULL);
    assert(len == 4);

    assert(creal(x[0]) == 1.0 && cimag(x[0]) == 0.0);
    assert(creal(x[1]) == 2.0 && cimag(x[1]) == 0.0);
    assert(creal(x[2]) == 3.0 && cimag(x[2]) == 0.0);
    assert(creal(x[3]) == 4.0 && cimag(x[3]) == 0.0);

    free(x);
    printf("test_read_sequence_valid: PASS\n");
}

void test_read_sequence_too_many() {
    int len;
    double complex *x = read_sequence("tests/test_data/too_long.txt", 4, &len);
    assert(x == NULL);  // Exceeds max_len, should return NULL
    printf("test_read_sequence_too_many: PASS\n");
}

int main() {
    test_read_sequence_valid();
    test_read_sequence_too_many();
    return 0;
}
