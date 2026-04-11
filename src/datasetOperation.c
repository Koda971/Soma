#include "datasetOperation.h"
#include "mnist.h"

double* getNormalizedImage(void *sample) {
	return ((Sample*)sample)->normalizedImage;
}

int* getLabel(void *sample) {
	return ((Sample*)sample)->label;
}

void* getNextSample(void *sample) {
	return ((Sample*)sample)->next;
}

const DatasetOperation datasetOperation = {
    .getNormalizedData = getNormalizedImage,
	.getLabel = getLabel,
	.getNextSample = getNextSample
};
