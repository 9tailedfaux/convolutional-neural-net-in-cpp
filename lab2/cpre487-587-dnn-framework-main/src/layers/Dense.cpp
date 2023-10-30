#include "Dense.h"

#include <iostream>
#include <vector>

#include "../Types.h"
#include "../Utils.h"
#include "Layer.h"
#include "Softmax.h"

namespace ML {
// --- Begin Student Code ---

// Compute the convultion for the layer data
void DenseLayer::computeNaive(const LayerData& dataIn) const {
    Array1D_fp32 inData = dataIn.getData<Array1D_fp32>();
    Array1D_fp32 outData = getOutputData().getData<Array1D_fp32>();
    Array2D_fp32 weights = weightData.getData<Array2D_fp32>();
    Array1D_fp32 biases = biasData.getData<Array1D_fp32>();

    LayerParams inputParams = getInputParams();
    size_t N = inputParams.dims[0];

    LayerParams outParams = getOutputParams();
    size_t M = outParams.dims[0];

    //size_t R = weightParam.dims[0];
    //size_t S = weightParam.dims[1];    
    
    for (u_int32_t m = 0; m < M; m++) {
        //printf("m: %d\n", (int)m);
        fp32 thisOutput = 0;
        for (u_int32_t n = 0; n < N; n++) {
            if (inData[n] > 100.0) {
                //printf("indata[%d]: %lf\n", (int)n, inData[n]);
            }
            
            thisOutput += (weights[n][m] * inData[n]);
            
        }
        outData[m] = thisOutput + biases[m];
    }
    softMax(outData, M);
    //printf("outdata: %lf\n", outData[200]);
}

void DenseLayer::computeQuantized(const LayerData& dataIn) const {
    Array1D_ui8 inData = dataIn.getData<Array1D_ui8>();
    Array1D_ui8 outData = getOutputData().getData<Array1D_ui8>();
    Array2D_i8 weights = weightData.getData<Array2D_i8>();
    Array1D_i32 biases = biasData.getData<Array1D_i32>();

    LayerParams inputParams = getInputParams();
    size_t N = inputParams.dims[0];

    LayerParams outParams = getOutputParams();
    size_t M = outParams.dims[0];

    //size_t R = weightParam.dims[0];
    //size_t S = weightParam.dims[1];    
    
    for (u_int32_t m = 0; m < M; m++) {
        //printf("m: %d\n", (int)m);
        fp32 thisOutput = 0;
        for (u_int32_t n = 0; n < N; n++) {
            if (inData[n] > 100.0) {
                //printf("indata[%d]: %lf\n", (int)n, inData[n]);
            }
            
            thisOutput += (weights[n][m] * inData[n]);
            
        }
        outData[m] = thisOutput + biases[m];
    }
    softMax(outData, M);
    //printf("outdata: %lf\n", outData[200]);
}

// Compute the convolution using threads
void DenseLayer::computeThreaded(const LayerData& dataIn) const {
    computeNaive(dataIn);
}

// Compute the convolution using a tiled approach
void DenseLayer::computeTiled(const LayerData& dataIn) const {
    computeNaive(dataIn);
}

// Compute the convolution using SIMD
void DenseLayer::computeSIMD(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}
}  // namespace ML