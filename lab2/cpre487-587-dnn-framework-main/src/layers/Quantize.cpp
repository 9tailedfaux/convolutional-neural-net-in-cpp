#include "Quantize.h"
#include "../Types.h"
#include <limits>
#include <cassert>
#include <vector>

namespace ML {

    void quantize_inputs (Array3D_fp32 input, Array3D_ui8 output, std::vector<size_t> dims) {
        quantize_3Darray<fp32, ui8>(input, output, dims, scale_inputs());
    }

    void quantize_biases (Array1D_fp32 input, Array1D_i32 output, std::vector<size_t> dims) {
        quantize_1Darray<fp32, i32>(input, output, dims, scale_biases());
    }

    void dequantize_biases (Array1D_i32 input, Array1D_fp32 output, std::vector<size_t> dims) {
        dequantize_1Darray<i32, fp32>(input, output, dims, scale_biases());
    }

    fp32 scale_biases() {
        return scale_weights() * scale_inputs();
    }

    fp32 scale_weights() {
        return scale<fp32, i8>(ABSMAX_WEIGHT);
    }

    fp32 scale_inputs() {
        return scale<fp32, ui8>(ABSMAX_INPUT);
    }
}