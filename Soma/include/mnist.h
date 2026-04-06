#ifndef MNIST_H
#define MNIST_H

typedef struct Sample {
    int originalImage[784]; // 28x28 pixels
    double normalizedImage[784];
    int label[10];

    struct Sample *next;
} Sample;

Sample *loadSamples(const char *imageFilePath, const char *labelFilePath);

void normalizeImages(Sample *head);

void freeSamples(Sample **head);

void printSamples(Sample *head);

#endif
