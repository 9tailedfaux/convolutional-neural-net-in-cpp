#include "MaxPooling.h"

#include <iostream>

#include "../Types.h"
#include "../Utils.h"
#include "Layer.h"

namespace ML {

void MaxPoolingLayer::computeNaive(const LayerData& dataIn) const {
    Array3D_fp32 inData = dataIn.getData<Array3D_fp32>();
    Array3D_fp32 outData = getOutputData().getData<Array3D_fp32>();

    LayerParams inputParams = getInputParams();
    LayerParams outputParams = getOutputParams();

    size_t width = outputParams.dims[0]; // Width of array
    size_t height = outputParams.dims[1]; // Height of array
    size_t channels = outputParams.dims[2]; // Number of channels, same for I/O

    size_t widthIndex = 0;
    size_t heightIndex = 0;

    for (uint32_t x = 0; x < channels; x++) {
        for (uint32_t y = 0; y < width; y++) {
                widthIndex = 2*y;
            for (uint32_t z = 0; z < height; z++) {

                heightIndex = 2*z;
                fp32 max = inData[widthIndex][heightIndex][x];
                if(max < inData[widthIndex + 1][heightIndex][x]){
                    max = inData[widthIndex + 1][heightIndex][x];
                }
                if(max < inData[widthIndex][heightIndex + 1][x]){
                    max = inData[widthIndex][heightIndex + 1][x];
                }
                if(max < inData[widthIndex + 1][heightIndex + 1][x]){
                    max = inData[widthIndex + 1][heightIndex + 1][x];
                }
                outData[y][z][x] = max;


            }
        }
    }
    
}

void MaxPoolingLayer::computeQuantized(const LayerData& dataIn) const {
    // TODO: Your Code Here...
    Array3D_ui8 inData = dataIn.getData<Array3D_ui8>();
    Array3D_ui8 outData = getOutputData().getData<Array3D_ui8>();

    LayerParams inputParams = getInputParams();
    LayerParams outputParams = getOutputParams();

    size_t inputWidth = inputParams.dims[0]; // Width of array
    size_t inputHeight = inputParams.dims[1]; // Height of array

    //size_t outputWidth = outputParams.dims[0];
    //size_t outputHeight = outputParams.dims[1];

    size_t channels = inputParams.dims[2]; // Number of channels, same for I/O

    for (uint32_t y = 0; y < inputWidth; y+=2) {
        for (uint32_t x = 0; x < inputHeight; x +=2) {
            for (uint32_t z = 0; z < channels; z++) {

                fp32 _1 = inData[x][y][z];
                fp32 _2 = inData[x+1][y][z];
                fp32 _3 = inData[x][y+1][z];
                fp32 _4 = inData[x+1][y+1][z];
                fp32 vals[4] = {_1, _2, _3, _4};
                fp32 max = vals[0];
                for (int i = 1; i < 4; i++) {
                    if (vals[i] > max) max = vals[i];
                }

                outData[x/2][y/2][z] = max;
                //printf("max: %lf\n", max);
            }
        }
    }
    
}

void MaxPoolingLayer::computeThreaded(const LayerData& dataIn) const {
    computeNaive(dataIn);
}

void MaxPoolingLayer::computeTiled(const LayerData& dataIn) const {
    computeNaive(dataIn);
}

void MaxPoolingLayer::computeSIMD(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}



}