#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "datasetOperation.h"

// Represents an entire layer
typedef struct {
    int inputSize;          // Number of neurons in the previous layer
    int layerSize;          // Number of neurons in this layer

    double *weights;        // 2D matrix flattened to 1D. Size = inputSize * layerSize
    double *biases;         // Size = layerSize
    
    double *activations;    // The output values after the activation function
    double *zValues;        // The raw values before activation (weights * input + bias)
    double *deltas;         // Error gradients for training
} Layer;

// Represents the network
typedef struct {
    int numberLayers;
    Layer *layers;
    double learningRate;
} NeuralNetwork;

typedef struct {
    void *trainData;
    void *testData;
    DatasetOperation datasetOperation;
} DatasetData;

typedef struct {
    int numEpochs;
    int miniBatchLength;
    double learningRate;
} NeuralNetworkParameters;

NeuralNetwork *createNeuralNetwork(int numberLayers, ...);

void train(NeuralNetwork *nn, DatasetData *datasetData, NeuralNetworkParameters *parameters);

void freeNeuralNetwork(NeuralNetwork **nn);

#endif
