#include "Flatten.h"

#include <iostream>
#include <vector>

#include "../Types.h"
#include "../Utils.h"
#include "Layer.h"
#include "Softmax.h"

namespace ML {
// --- Begin Student Code ---

void FlattenLayer::computeNaive(const LayerData& dataIn) const {
    Array3D_fp32 inData = dataIn.getData<Array3D_fp32>();
    Array1D_fp32 outData = getOutputData().getData<Array1D_fp32>();

    LayerParams inputParams = getInputParams();
    LayerParams outputParams = getOutputParams();

    size_t inputWidth = inputParams.dims[0];
    size_t inputHeight = inputParams.dims[1];
    size_t channels = inputParams.dims[2];

    int foo = 0; //Used to iterate through output array(?)

    for (uint32_t i = 0; i < channels; i++) {
        for (uint32_t j = 0; j < inputHeight; j++) {
            for (uint32_t k = 0; k < inputWidth; k++) {
                outData[foo++] = inData[i][j][k];
            }
        }
    }

}

// Compute the convolution using threads
void FlattenLayer::computeThreaded(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

// Compute the convolution using a tiled approach
void FlattenLayer::computeTiled(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

// Compute the convolution using SIMD
void FlattenLayer::computeSIMD(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}
}  // namespace ML