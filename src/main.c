#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mnist.h"
#include "neuralNetwork.h"
#include "utils.h"

int main() {
    Sample *trainData = loadSamples("resources/data/train-images.idx3-ubyte",
            "resources/data/train-labels.idx1-ubyte");
    Sample *testData =  loadSamples("resources/data/t10k-images.idx3-ubyte",
            "resources/data/t10k-labels.idx1-ubyte");

    normalizeImages(trainData);
    normalizeImages(testData);

    srand(time(NULL));

    printf("build nn start = [784, 30, 10]\n");
    NeuralNetwork *nn = createNeuralNetwork(3, 784, 30, 10);
    printf("build nn end\n");

    DatasetData datasetData; 
    datasetData.trainData = trainData;
    datasetData.testData = testData;
    datasetData.datasetOperation = datasetOperation;

    NeuralNetworkParameters nnParameters;
    nnParameters.numEpochs = 1;
    nnParameters.miniBatchLength = 1;
    nnParameters.learningRate = 1;

    train(nn, &datasetData, &nnParameters);

    //printSamples(trainData);
    
    freeSamples(&trainData);
    freeSamples(&testData);

    freeNeuralNetwork(&nn);

    return 0;
}

