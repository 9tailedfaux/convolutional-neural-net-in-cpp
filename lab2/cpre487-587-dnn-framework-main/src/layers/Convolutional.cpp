#include "Convolutional.h"

#include <iostream>
#include <vector>
#include <thread>

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

    for (uint32_t p = 0; p < P; p++) {
        //printf("Checkpoint 4. m = %d\n", m);
        for (uint32_t q = 0; q < Q; q++) {
            //printf("Checkpoint 5. p = %d\n", p);
            for (uint32_t m = 0; m < M; m++) {
                //printf("Checkpoint 6. q = %d\n", q);
                fp32 thisOutput = 0;
                for (uint32_t r = 0; r < R; r++) {
                    //printf("Checkpoint 7. c = %d\n", c);
                    for (uint32_t s = 0; s < S; s++) { 
                        //printf("Checkpoint 8. r = %d\n", r);
                        for (uint32_t c = 0; c < C; c += 1) { //lol
                            //printf("Checkpoint 9. s = %d\n", s);

                            thisOutput += ((inData[UP + r][UQ + s][c] * filter[r][s][c][m]));
                        }
                    }
                }
                outData[p][q][m] = relu(thisOutput + biases[m]);
            }
        }
    }

    
    //printf("%lf", data[0][0][0]);

}

void ConvolutionalLayer::computeQuantized(const LayerData& dataIn) const {
    Array3D_ui8 inData = dataIn.getData<Array3D_ui8>();
    Array3D_ui8 outData = getOutputData().getData<Array3D_ui8>();
    Array4D_i8 filter = weightData.getData<Array4D_i8>();
    Array1D_i32 biases = biasData.getData<Array1D_i32>();

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

    for (uint32_t p = 0; p < P; p++) {
        //printf("Checkpoint 4. m = %d\n", m);
        for (uint32_t q = 0; q < Q; q++) {
            //printf("Checkpoint 5. p = %d\n", p);
            for (uint32_t m = 0; m < M; m++) {
                //printf("Checkpoint 6. q = %d\n", q);
                fp32 thisOutput = 0;
                for (uint32_t r = 0; r < R; r++) {
                    //printf("Checkpoint 7. c = %d\n", c);
                    for (uint32_t s = 0; s < S; s++) { 
                        //printf("Checkpoint 8. r = %d\n", r);
                        for (uint32_t c = 0; c < C; c += 1) { //lol
                            //printf("Checkpoint 9. s = %d\n", s);

                            thisOutput += ((inData[UP + r][UQ + s][c] * filter[r][s][c][m]));
                        }
                    }
                }
                outData[p][q][m] = relu(thisOutput + biases[m]);
            }
        }
    }

    
    //printf("%lf", data[0][0][0]);

}

void threadFunction(
    Array3D_fp32 inData, 
    Array4D_fp32 filter, 
    fp32* thisOutput, 
    short UP, 
    short UQ,
    uint32_t m,
    size_t R,
    size_t S,
    size_t C,
    Array1D_fp32 biases
    ) {
        //printf("thread launched\n");
        std::this_thread::yield();

        for (uint32_t r = 0; r < R; r++) {
            //printf("Checkpoint 7. c = %d\n", c);
            for (uint32_t s = 0; s < S; s++) { 
                //printf("Checkpoint 8. r = %d\n", r);
                for (uint32_t c = 0; c < C; c += 1) { //lol
                    //printf("Checkpoint 9. s = %d\n", s);

                    *thisOutput += ((inData[UP + r][UQ + s][c] * filter[r][s][c][m]));
                    //printf("successfully set thisOutput\n");
                    
                }
            }
        }
        *thisOutput = relu(*thisOutput + biases[m]);
}

// Compute the convolution using threads
void ConvolutionalLayer::computeThreaded(const LayerData& dataIn) const {
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

    size_t numThreads = 64;
    //numThreads = numThreads ? numThreads : 4;
    printf("numThreads: %d\n", (int)numThreads);
    //std::thread* threads = (std::thread*)malloc(numThreads * sizeof(std::thread));
    std::vector<std::thread> threads;

    
    //uint32_t threadIndex = 0;

    for (uint32_t p = 0; p < P; p++) {
        //printf("Checkpoint 4. m = %d\n", m);
        for (uint32_t q = 0; q < Q; q++) {
            //printf("Checkpoint 5. p = %d\n", p);
            for (uint32_t m = 0; m < M; m++) {
                //printf("Checkpoint 6. q = %d\n", q);
                fp32* thisOutput = &outData[p][q][m];

                //printf("pushing thread to vector\n");
                
                threads.push_back(
                    std::thread (
                        threadFunction, 
                        inData, 
                        filter, 
                        thisOutput, 
                        UP, 
                        UQ, 
                        m, 
                        R, 
                        S, 
                        C, 
                        biases
                    )
                );

                //printf("checking against max threads\n");

                //printf("threads.size: %d\n", (int)threads.size());

                if (threads.size() >= numThreads) {
                    //printf("joining all threads\n");
                    for (auto thread = threads.begin(); thread != threads.end(); thread++) {
                        thread->join();
                    }
                    threads.clear();
                    threads.shrink_to_fit();
                }

                //printf("successfully pushed thread to vector\n");
            }
        }
    }

    for (auto thread = threads.begin(); thread != threads.end(); thread++) {
        thread->join();
    }

    printf("succcessfully launched threads\n");

    //join all threads so we don't continue to the next layer until all of this is done
    

    //free(threads);
}

// Compute the convolution using a tiled approach
void ConvolutionalLayer::computeTiled(const LayerData& dataIn) const {
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

    uint8_t T = 1; //tile factor
    uint16_t CT = C / T;
    uint16_t MT = M / T;

    for (uint16_t p = 0; p < P; p++) {
        //printf("Checkpoint 4. m = %d\n", m);
        for (uint16_t q = 0; q < Q; q++) {
            //printf("Checkpoint 5. p = %d\n", p);
            
            //printf("Checkpoint 6. q = %d\n", q);
            for (uint16_t r = 0; r < R; r++) {
                //printf("Checkpoint 7. c = %d\n", c);
                for (uint16_t s = 0; s < S; s++) { 
                    //printf("Checkpoint 8. r = %d\n", r);
                    for (uint8_t ct = 0; ct < T; ct++) {

                        for (uint8_t mt = 0; mt < T; mt++){
                            for (uint16_t c = ct * CT; c < CT * (ct + 1); c += 1) { //lol
                                //printf("Checkpoint 9. s = %d\n", s);

                                for (uint16_t m = mt * MT; m < MT * (mt + 1); m++) {
                                    
                                    if (c == 0 && r == 0 && s == 0) outData[p][q][m] = 0;

                                    outData[p][q][m] += ((inData[UP + r][UQ + s][c] * filter[r][s][c][m]));

                                    if (c == C - 1 && r == R - 1 && s == S - 1) outData[p][q][m] = relu(outData[p][q][m] + biases[m]);
                                }
                            }
                        }
                    }
                    
                }
            }
        }
    }
}

// Compute the convolution using SIMD
void ConvolutionalLayer::computeSIMD(const LayerData& dataIn) const {
    // TODO: Your Code Here...
}

fp32 relu(const fp32 input) { return input < 0 ? 0 : input; }
short stride(const size_t inDim, const size_t outDim, const size_t filterDim) { return (short)((inDim - filterDim) / (outDim - 1)); }
}  // namespace ML