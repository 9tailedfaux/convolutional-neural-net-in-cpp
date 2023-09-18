#include "MaxPooling.h"

#include <iostream>

#include "../Types.h"
#include "../Utils.h"
#include "Layer.h"

namespace ML {

void MaxPoolingLayer::computeNaive(const LayerData& dataIn) const {
    // TODO: Your Code Here...
    Array3D_fp32 inData = dataIn.getData<Array3D_fp32>();
    Array3D_fp32 outData = getOutputData().getData<Array3D_fp32>();

    LayerParams inputParams = getInputParams();
    LayerParams outputParams = getOutputParams();

    size_t inputWidth = inputParams.dims[0]; // Width of array
    size_t inputHeight = inputParams.dims[1]; // Height of array

    size_t outputWidth = outputParams.dims[0];
    size_t outputHeight = outputParams.dims[1];

    size_t channels = inputParams.dims[2]; // Number of channels, same for I/O

    for (uint32_t x = 0; x < inputWidth; x+=2) {
        for (uint32_t y = 0; y < inputHeight; y +=2) {
            for (uint32_t channelDepth = 0; channelDepth < outputParams; channelDepth++) {
                
            }
        }
    }
    
}

void MaxPoolingLayer::computeThreaded(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

void MaxPoolingLayer::computeTiled(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

void MaxPoolingLayer::computeSIMD(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}



}