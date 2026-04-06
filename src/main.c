#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mnist.h"
#include "neuralNetwork.h"

int main() {
    Sample *trainData = loadSamples("resources/data/train-images.idx3-ubyte",
            "resources/data/train-labels.idx1-ubyte");
    Sample *testData =  loadSamples("resources/data/t10k-images.idx3-ubyte",
            "resources/data/t10k-labels.idx1-ubyte");

    normalizeImages(trainData);
    normalizeImages(testData);

    srand(time(NULL));

    DenseNeuralNetwork *nn = createDenseNeuralNetwork(3, 784, 30, 10);

    printSamples(trainData);
    
    freeSamples(&trainData);
    freeSamples(&testData);

    freeDenseNeuralNetwork(&nn);

    return 0;
}
