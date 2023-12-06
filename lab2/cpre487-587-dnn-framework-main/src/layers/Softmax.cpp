
#include "Softmax.h"
#include "../Types.h"
#include <cmath>
#include <cstdio>

namespace ML {

void SoftmaxLayer::computeNaive(const LayerData& dataIn) const {
   Array1D_fp32 inData = dataIn.getData<Array1D_fp32>();
   Array1D_fp32 outData = getOutputData().getData<Array1D_fp32>();

   fp32 sum;

   for(int i = 0; i < (int) getOutputParams().dims[0]; i++){
        sum = 0.0;
        for(int j = 0; j < (int) getInputParams().dims[0]; j++){
            sum += exp(inData[j]);
        }
        outData[i] = exp(inData[i])/sum;
   }
}

void SoftmaxLayer::computeQuantized(const LayerData& dataIn) const {
   Array1D_ui8 inData = dataIn.getData<Array1D_ui8>();
   Array1D_ui8 outData = getOutputData().getData<Array1D_ui8>();

   ui8 sum;

   for(int i = 0; i < (int) getOutputParams().dims[0]; i++){
        sum = 0.0;
        for(int j = 0; j < (int) getInputParams().dims[0]; j++){
            sum += exp(inData[j]);
        }
        outData[i] = exp(inData[i])/sum;
   }
}

// Compute the convolution using threads
void SoftmaxLayer::computeThreaded(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

// Compute the convolution using a tiled approach
void SoftmaxLayer::computeTiled(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

// Compute the convolution using SIMD
void SoftmaxLayer::computeSIMD(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}



}