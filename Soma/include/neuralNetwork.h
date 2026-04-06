#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

// Represents an entire "Dense" (Fully Connected) level
typedef struct {
    int inputSize;          // Number of neurons in the previous layer
    int layerSize;          // Number of neurons in this layer

    double *weights;        // 2D matrix flattened to 1D. Size = inputSize * layerSize
    double *biases;         // Size = layerSize
    
    double *activations;    // The output values after the activation function
    double *zValues;        // The raw values before activation (weights * input + bias)
    double *deltas;         // Error gradients for training
} DenseLayer;

// Represents the network
typedef struct {
    int numberLayers;
    DenseLayer *layers;
    double learningRate;
} DenseNeuralNetwork;

DenseNeuralNetwork *createDenseNeuralNetwork(int numberLayers, ...);

void freeDenseNeuralNetwork(DenseNeuralNetwork **nn);

#endif
