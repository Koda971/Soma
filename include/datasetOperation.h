#ifndef DATASET_OPERATION_H
#define DATASET_OPERATION_H

typedef double* (*GetNormalizedData)(void *sample);
typedef int* (*GetLabel)(void *sample);
typedef void* (*GetNextSample)(void *sample);

typedef struct {
	GetNormalizedData getNormalizedData;
	GetLabel getLabel;
	GetNextSample getNextSample;
} DatasetOperation;

extern const DatasetOperation datasetOperation;

double* getNormalizeData(void *sample);

int* getLabel(void *sample);

void* getNextSample(void *sample);

#endif
