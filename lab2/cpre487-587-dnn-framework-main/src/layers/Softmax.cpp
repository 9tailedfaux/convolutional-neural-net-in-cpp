
#include "Softmax.h"
#include "../Types.h"
#include <cmath>

namespace ML {
void softMax(Array1D_fp32 input, size_t size) {
    fp32 bottomSum = 0;
    for (uint32_t n = 0; n < size; n++) {
        bottomSum += exp(input[n]);
    }
    for (uint32_t n = 0; n < size; n++) {
        input[n] = exp(input[n]) / bottomSum;
    }
}
}