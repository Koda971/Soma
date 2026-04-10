typedef double* (*GetNormalizedData)(void *sample);
typedef int* (*GetLabel)(void *sample);
typedef void* (*GetNextSample)(void *sample);

typedef struct {
	GetNormalizedData getNormalizedData;
	GetLabel getLabel;
	GetNextSample getNextSample;
} DatasetOperation;

