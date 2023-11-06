#pragma once
#include "../Types.h"
#include <cassert>
#include <limits>

namespace ML {
    #define ABSMAX_WEIGHT 1.3241188526153564
    #define ABSMAX_BIAS 0.23974871635437012
    #define ABSMAX_INPUT 1.0

    template <typename Iv, typename Ov> void quantize_2Darray(Iv** input, Ov** output, std::vector<size_t> dims, fp32 scale);
    template <typename Iv, typename Ov> void quantize_4Darray(Iv**** input, Ov**** output, std::vector<size_t> dims, fp32 scale);

    fp32 scale_biases(void);
    fp32 scale_weights(void);
    fp32 scale_inputs(void);

    template <typename I, typename O> O quantize(I input, fp32 scale) {
        return (O)(scale * input);
    }
    template <typename I, typename O> O dequantize(I input, fp32 scale) {
        return (O)(input / scale);
    }

    template <typename I, typename O> void quantize_weights (I input, O output, std::vector<size_t> dims) {
        assert(typeid(I) == typeid(Array2D_fp32) || typeid(I) == typeid(Array4D_fp32));

        if (typeid(I) == typeid(Array2D_fp32)) {
            assert(typeid(O) == typeid(Array2D_i8));
            quantize_2Darray<fp32, i8>(input, output, dims, scale_weights());
        }
        else if (typeid(I) == typeid(Array4D_fp32)) {
            assert(typeid(O) == typeid(Array4D_i8));
            quantize_4Darray<fp32, i8>(input, output, dims, scale_weights());
        } else {
            return;
        }
    }
    void quantize_inputs (Array3D_fp32 input, Array3D_ui8 output, std::vector<size_t> dims);
    void quantize_biases (Array1D_fp32 input, Array1D_i32 output, std::vector<size_t> dims);

    template <typename Iv, typename Ov> void quantize_1Darray(Iv* input, Ov* output, std::vector<size_t> dims, fp32 scale) {
        for(uint32_t i = 0; i < dims[0]; i++) {
            output[i] = quantize<Iv, Ov>(input[i], scale);
        }
    }
    template <typename Iv, typename Ov> void quantize_2Darray(Iv** input, Ov** output, std::vector<size_t> dims, fp32 scale) {
        for(uint32_t i = 0; i < dims[0]; i++) {
            for(uint32_t j = 0; j < dims[1]; j++) {
                output[i][j] = quantize<Iv, Ov>(input[i][j], scale);
            }
        }
    }
    template <typename Iv, typename Ov> void quantize_3Darray(Iv*** input, Ov*** output, std::vector<size_t> dims, fp32 scale) {
        for(uint32_t i = 0; i < dims[0]; i++) {
            for(uint32_t j = 0; j < dims[1]; j++) {
                for (uint32_t k = 0; k < dims[2]; k++) {
                    output[i][j][k] = quantize<Iv, Ov>(input[i][j][k], scale);
                }
            }
        }
    }
    template <typename Iv, typename Ov> void quantize_4Darray(Iv**** input, Ov**** output, std::vector<size_t> dims, fp32 scale) {
        for(uint32_t i = 0; i < dims[0]; i++) {
            for(uint32_t j = 0; j < dims[1]; j++) {
                for (uint32_t k = 0; k < dims[2]; k++) {
                    for (uint32_t l = 0; l < dims[3]; l++) {
                        output[i][j][k][l] = quantize<Iv, Ov>(input[i][j][k][l], scale);               
                    }
                }
            }
        }
    }

    template <typename Iv, typename Ov> void dequantize_1Darray(Iv* input, Ov* output, std::vector<size_t> dims, fp32 scale) {
        for(uint32_t i = 0; i < dims[0]; i++) {
            output[i] = dequantize<Iv, Ov>(input[i], scale);
        }
    }
    template <typename Iv, typename Ov> void dequantize_2Darray(Iv** input, Ov** output, std::vector<size_t> dims, fp32 scale) {
        for(uint32_t i = 0; i < dims[0]; i++) {
            for(uint32_t j = 0; j < dims[1]; j++) {
                output[i][j] = dequantize<Iv, Ov>(input[i][j], scale);
            }
        }
    }
    template <typename Iv, typename Ov> void dequantize_3Darray(Iv*** input, Ov*** output, std::vector<size_t> dims, fp32 scale) {
        for(uint32_t i = 0; i < dims[0]; i++) {
            for(uint32_t j = 0; j < dims[1]; j++) {
                for (uint32_t k = 0; k < dims[2]; k++) {
                    output[i][j][k] = dequantize<Iv, Ov>(input[i][j][k], scale);
                }
            }
        }
    }
    template <typename Iv, typename Ov> void dequantize_4Darray(Iv**** input, Ov**** output, std::vector<size_t> dims, fp32 scale) {
        for(uint32_t i = 0; i < dims[0]; i++) {
            for(uint32_t j = 0; j < dims[1]; j++) {
                for (uint32_t k = 0; k < dims[2]; k++) {
                    for (uint32_t l = 0; l < dims[3]; l++) {
                        output[i][j][k][l] = dequantize<Iv, Ov>(input[i][j][k][l], scale);               
                    }
                }
            }
        }
    }

    template <typename I, typename O> void dequantize_weights(I input, O output, std::vector<size_t> dims) {
        assert(typeid(I) == typeid(Array2D_i8) || typeid(I) == typeid(Array4D_i8));

        if (typeid(I) == typeid(Array2D_i8)) {
            assert(typeid(O) == typeid(Array2D_fp32));
            dequantize_2Darray<i8, fp32>(input, output, dims, scale_weights());
        }
        else if (typeid(I) == typeid(Array4D_i8)) {
            assert(typeid(O) == typeid(Array4D_fp32));
            dequantize_4Darray<i8, fp32>(input, output, dims, scale_weights());
        } else {
            return;
        }
    }
    template <typename I, typename O> void dequantize_inputs (I input, O output, std::vector<size_t> dims) {
        assert(typeid(I) == typeid(Array1D_ui8) || typeid(I) == typeid(Array3D_ui8));

        if (typeid(I) == typeid(Array1D_ui8)) {
            assert(typeid(O) == typeid(Array1D_fp32));
            dequantize_1Darray<ui8, fp32>(input, output, dims, scale_inputs());
        }
        else if (typeid(I) == typeid(Array3D_ui8)) {
            assert(typeid(O) == typeid(Array3D_fp32));
            dequantize_3Darray<ui8, fp32>(input, output, dims, scale_inputs());
        } else {
            return;
        }
    }
    void dequantize_biases (Array1D_i32 input, Array1D_fp32 output, std::vector<size_t> dims);
    
    template <typename I, typename R> fp32 scale(I absolute_max) {
        return (std::numeric_limits<R>::max() / absolute_max);
    }
}