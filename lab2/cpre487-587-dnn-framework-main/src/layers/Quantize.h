#pragma once
#include "../Types.h"
#include <limits>

namespace ML {
    #define ABSMAX_WEIGHT 1.3241188526153564
    #define ABSMAX_BIAS 0.23974871635437012
    #define ABSMAX_INPUT 1.0

    template <typename I, typename O> O quantize(I input, fp32 scale);
    template <typename I, typename O> O dequantize(I input, fp32 scale) {
        return (O)(input / scale);
    }

    template <typename I, typename O> void quantize_weights (I input, O output, std::vector<size_t> dims);
    void quantize_inputs (Array3D_fp32 input, Array3D_ui8 output, std::vector<size_t> dims);
    void quantize_biases (Array1D_fp32 input, Array1D_i32 output, std::vector<size_t> dims);

    template <typename Iv, typename Ov> void quantize_1Darray(Iv* input, Ov* output, std::vector<size_t> dims, fp32 scale);
    template <typename Iv, typename Ov> void quantize_2Darray(Iv** input, Ov** output, std::vector<size_t> dims, fp32 scale);
    template <typename Iv, typename Ov> void quantize_3Darray(Iv*** input, Ov*** output, std::vector<size_t> dims, fp32 scale);
    template <typename Iv, typename Ov> void quantize_4Darray(Iv**** input, Ov**** output, std::vector<size_t> dims, fp32 scale);

    template <typename Iv, typename Ov> void dequantize_1Darray(Iv* input, Ov* output, std::vector<size_t> dims, fp32 scale) {
        for(uint32_t i = 0; i < dims[0]; i++) {
            output[i] = dequantize<Iv, Ov>(input[i], scale);
        }
    }
    template <typename Iv, typename Ov> void dequantize_2Darray(Iv** input, Ov** output, std::vector<size_t> dims, fp32 scale);
    template <typename Iv, typename Ov> void dequantize_3Darray(Iv*** input, Ov*** output, std::vector<size_t> dims, fp32 scale) {
        for(uint32_t i = 0; i < dims[0]; i++) {
            for(uint32_t j = 0; j < dims[1]; j++) {
                for (uint32_t k = 0; k < dims[2]; k++) {
                    output[i][j][k] = dequantize<Iv, Ov>(input[i][j][k], scale);
                }
            }
        }
    }
    template <typename Iv, typename Ov> void dequantize_4Darray(Iv**** input, Ov**** output, std::vector<size_t> dims, fp32 scale);

    template <typename I, typename O> void dequantize_weights(I input, O output, std::vector<size_t> dims);
    template <typename I, typename O> void dequantize_inputs (I input, O output, std::vector<size_t> dims);
    void dequantize_biases (Array1D_i32 input, Array1D_fp32 output, std::vector<size_t> dims);
    
    template <typename I, typename R> fp32 scale(I absolute_max) {
        return (std::numeric_limits<R>::max() / absolute_max);
    }
    fp32 scale_biases(void);
    fp32 scale_weights(void);
    fp32 scale_inputs(void);
}