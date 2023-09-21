#include "Softmax.h"

#include <iostream>

#include "../Types.h"
#include "../Utils.h"
#include "Layer.h"

namespace ML {

void SoftmaxLayer::computeNaive(const LayerData& dataIn) const {
    //TODO: Code go here
    Array1D_fp32 inData = dataIn.getData<Array1D_fp32>();
    Array1D_fp32 outData = getOutputData().getData<Array1D_fp32>();

    LayerParams inputParams = getInputParams();
    LayerParams outputParams = getOutputParams();

    size_t size = inputParams.dims[0];

    fp32 bottomSum = 0;
    for (uint32_t n = 0; n < size; n++) {
        bottomSum += exp(inData[n]);
    }
    for (uint32_t n = 0; n < size; n++) {
        outData[n] = exp(inData[n]) / bottomSum;
    }
    
}

void SoftmaxLayer::computeThreaded(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

void SoftmaxLayer::computeTiled(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

void SoftmaxLayer::computeSIMD(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}



}