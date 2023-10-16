
#include "Softmax.h"
#include "../Types.h"
#include <cmath>
#include <cstdio>

namespace ML {
void softMax(Array1D_fp32 input, size_t size) {
    fp32 bottomSum = 0;
    for (uint32_t n = 0; n < size; n++) {
        if (input[n] > 100.0) {
            //printf("input[%d]: %lf\n", (int)n, input[n]);
        }
        bottomSum += exp(input[n]);
    }
    for (uint32_t n = 0; n < size; n++) {
        input[n] = exp(input[n]) / bottomSum;
    }
}
}