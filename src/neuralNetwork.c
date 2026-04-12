#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include "neuralNetwork.h"
#include "utils.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ################################### PRIVATE FUNCTIONS DECLARATIONS ################################

static void initLayer(Layer *layer, int inputs, int neurons);

static void allocateLayer(Layer *layer, int inputs, int neurons);

static void initializeLayerRandom(Layer *layer);

// Function to generate a number with normal distribution (Box-Muller approximation)
static double nextGaussian();

static void freeLayer(Layer *layer);

// ###################################################################################################

// ################################### PUBLIC FUNCTIONS IMPLEMENTATIONS ##############################

// This function uses the "rand()" method. For this function to work properly, the caller must first call
// the "srand" method.
NeuralNetwork *createNeuralNetwork(int numberLayers, ...) {
    NeuralNetwork *nn = xmalloc(sizeof(NeuralNetwork));
    nn->numberLayers = numberLayers;
    nn->layers = xmalloc(numberLayers * sizeof(Layer));
    // TODO
    // nn->learningRate = ;

    va_list arguments;
    va_start(arguments, numberLayers);
    int inputs = -1; // The first layer has not inputs;
    for (int i = 0; i < numberLayers; i++) {
        int neurons = va_arg(arguments, int);
        initLayer(&nn->layers[i], inputs, neurons);
        inputs = neurons;
    }
    va_end(arguments);

    return nn;
}

void train(NeuralNetwork *nn, DatasetData *datasetData, NeuralNetworkParameters *parameters) {
    for (int i = 0; i < 10; i++) {
        printf("%d", datasetOperation.getLabel(datasetData->trainData)[i]);
    }
}

void freeNeuralNetwork(NeuralNetwork **nn) {
    if (nn == NULL || *nn == NULL) return;

    for(int i = 0; i < (*nn)->numberLayers; i++) {
        freeLayer(&(*nn)->layers[i]);
    }
    free((*nn)->layers);
    free(*nn);

    *nn = NULL;
}

// ###################################################################################################

// ################################### PRIVATE FUNCTIONS IMPLEMENTATIONS  ############################
static void initLayer(Layer *layer, int inputs, int neurons) {
   allocateLayer(layer, inputs, neurons);
   initializeLayerRandom(layer);
}

static void allocateLayer(Layer *layer, int inputs, int neurons) {    
    layer->inputSize = inputs;
    layer->layerSize = neurons;

    if (inputs == -1) {
        layer->weights     = NULL;
        layer->biases      = NULL;
        layer->activations = NULL;
        layer->zValues     = NULL;
        layer->deltas      = NULL;

        return;
    }

    layer->weights     = xmalloc(inputs * neurons * sizeof(double));
    layer->biases      = xmalloc(neurons * sizeof(double));
    layer->activations = xmalloc(neurons * sizeof(double));
    layer->zValues     = xmalloc(neurons * sizeof(double));
    layer->deltas      = xmalloc(neurons * sizeof(double));
}

static void initializeLayerRandom(Layer *layer) {
   if (layer->inputSize == -1) return;
   
   for(int i = 0; i < layer->layerSize; i++) {
       layer->biases[i] = nextGaussian();
   }

   int totalWeights = layer->inputSize * layer->layerSize;
   for(int i = 0; i < totalWeights; i++) {
       layer->weights[i] = nextGaussian();
   }
}

static double nextGaussian() {
    double u1 = (double)rand() / RAND_MAX;
    double u2 = (double)rand() / RAND_MAX;
    
    // Avoid having u1 be exactly 0 to avoid causing a log(0) math error
    while (u1 == 0.0) {
        u1 = (double)rand() / RAND_MAX;
    }

    // Apply the Box-Muller formula to obtain a Gaussian value
    return sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}

static void freeLayer(Layer *layer) {
    free(layer->weights);
    free(layer->biases);
    free(layer->activations);
    free(layer->zValues);
    free(layer->deltas);
}

// ###################################################################################################
