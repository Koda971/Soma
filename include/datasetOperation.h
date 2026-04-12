#ifndef DATASET_OPERATION_H
#define DATASET_OPERATION_H

typedef double* (*GetData)(void *sample);
typedef int* (*GetLabel)(void *sample);
typedef void* (*GetNextSample)(void *sample);

typedef struct {
	GetData getData;
	GetLabel getLabel;
	GetNextSample getNextSample;
} DatasetOperation;

extern const DatasetOperation datasetOperation;

double* getData(void *sample);

int* getLabel(void *sample);

void* getNextSample(void *sample);

#endif
