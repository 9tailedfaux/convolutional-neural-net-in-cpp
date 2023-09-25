#include "Convolutional.h"

#include <iostream>
#include <vector>

#include "../Types.h"
#include "../Utils.h"
#include "Layer.h"

namespace ML {
// --- Begin Student Code ---

// Compute the convultion for the layer data
void ConvolutionalLayer::computeNaive(const LayerData& dataIn) const {
    Array3D_fp32 inData = dataIn.getData<Array3D_fp32>();
    Array3D_fp32 outData = getOutputData().getData<Array3D_fp32>();
    Array4D_fp32 filter = weightData.getData<Array4D_fp32>();
    Array1D_fp32 biases = biasData.getData<Array1D_fp32>();

    LayerParams inputParams = getInputParams();
    size_t C = inputParams.dims[2]; //channels in input
    size_t W = inputParams.dims[0]; //width of input
    size_t H = inputParams.dims[1]; //height of input

    LayerParams outParams = getOutputParams();
    size_t M = outParams.dims[2]; //channels in output
    size_t Q = outParams.dims[0]; //width of output
    size_t P = outParams.dims[1]; //height of output

    size_t R = weightParam.dims[0]; //height of filter
    size_t S = weightParam.dims[1]; //width of filter

    //printf("Checkpoint 3\n");

    short UP = stride(H, P, R);
    short UQ = stride(W, Q, S);

    for (uint32_t m = 0; m < M; m++) {
        //printf("Checkpoint 4. m = %d\n", m);
        for (uint32_t p = 0; p < P; p++) {
            //printf("Checkpoint 5. p = %d\n", p);
            for (uint32_t q = 0; q < Q; q++) {
                //printf("Checkpoint 6. q = %d\n", q);
                fp32 thisOutput = 0;
                for (uint32_t c = 0; c < C; c += 1) { //fuck you
                    //printf("Checkpoint 7. c = %d\n", c);
                    for (uint32_t r = 0; r < R; r++) {
                        //printf("Checkpoint 8. r = %d\n", r);
                        for (uint32_t s = 0; s < S; s++) {
                            //printf("Checkpoint 9. s = %d\n", s);

                            thisOutput += ((inData[UQ + s][UP + r][c] * filter[s][r][c][m]));
                        }
                    }
                }
                outData[q][p][m] = relu(thisOutput + biases[m]);
            }
        }
    }

    
    //printf("%lf", data[0][0][0]);

}

// Compute the convolution using threads
void ConvolutionalLayer::computeThreaded(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

// Compute the convolution using a tiled approach
void ConvolutionalLayer::computeTiled(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

// Compute the convolution using SIMD
void ConvolutionalLayer::computeSIMD(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

fp32 relu(const fp32 input) { return input < 0 ? 0 : input; }
short stride(const size_t inDim, const size_t outDim, const size_t filterDim) { return (short)((inDim - filterDim) / (outDim - 1)); }
}  // namespace ML