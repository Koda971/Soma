#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "mnist.h"
#include "datasetOperation.h"
#include "utils.h"

// ################################### PRIVATE FUNCTIONS ##########################################

// Utility per invertire l'ordine dei byte (Big-Endian -> Little-Endian)
static uint32_t swapEndian(uint32_t val) {
    return ((val << 24) & 0xff000000) |
           ((val <<  8) & 0x00ff0000) |
           ((val >>  8) & 0x0000ff00) |
           ((val >> 24) & 0x000000ff);
}

// Utility per leggere un intero da file e sistemarne l'Endianness
static uint32_t readInt(FILE *f) {
    uint32_t val;
    size_t read_count = fread(&val, sizeof(uint32_t), 1, f);

    if (read_count != 1) {
        if (feof(f)) {
            fprintf(stderr, "Errore: Fine del file raggiunta inaspettatamente.\n");
        } else if (ferror(f)) {
            perror("Errore critico durante la lettura del file");
        } else {

            fprintf(stderr, "Errore: Letti %zu elementi invece di 1.\n", read_count);
        }
        exit(EXIT_FAILURE);
    }
    return swapEndian(val);
}

static void normalizeImage(Sample *sample) {
    if (sample == NULL) return;

    int n = 784;
    double media = 0;

    // 1. Calcolo della Media (Mean)
    for (int i = 0; i < n; i++) {
        media += sample->originalImage[i];
    }
    media /= n;

    // 2. Calcolo della Deviazione Standard (Std)
    double std = 0;
    for (int i = 0; i < n; i++) {
        // pow(x, 2) eleva al quadrato
        std += pow(sample->originalImage[i] - media, 2);
    }
    
    // Calcoliamo la radice quadrata della varianza
    std = sqrt(std / n);

    // 3. Normalizzazione (Z-score)
    // Nota: aggiungiamo un epsilon (1e-7) per evitare la divisione per zero 
    // se l'immagine è completamente piatta (tutti i pixel uguali).
    if (std < 1e-7) std = 1.0; 

    for (int i = 0; i < n; i++) {
        sample->normalizedImage[i] = (sample->originalImage[i] - media) / std;
    }
}

// ###############################################################################################

// ####################################### DatasetOperation #######################################################
    static double* getNormalizedImage(void *sample) {
	return ((Sample*)sample)->normalizedImage;
    }

    static int* getLabel(void *sample) {
	return ((Sample*)sample)->label;
    }

    static void* getNextSample(void *sample) {
	return ((Sample*)sample)->next;
    }

    const DatasetOperation datasetOperation = {
    	.getNormalizedData = getNormalizedImage,
	    .getLabel = getLabel,
	    .getNextSample = getNextSample
    };
// ###############################################################################################

// ###############################################################################################

Sample* loadSamples(const char *imageFilePath, const char *labelFilePath) {
    FILE *dataF = xfopen(imageFilePath, "rb");
    FILE *labelF = xfopen(labelFilePath, "rb");

    uint32_t magicNumber = readInt(dataF);
    uint32_t numberOfItems = readInt(dataF);
    uint32_t nRows = readInt(dataF);
    uint32_t nCols = readInt(dataF);

    printf("magic number is %u\n", magicNumber);
    printf("number of items is %u\n", numberOfItems);
    printf("number of rows is: %u\n", nRows);
    printf("number of cols is: %u\n", nCols);

    uint32_t labelMagicNumber = readInt(labelF);
    uint32_t numberOfLabels = readInt(labelF);

    printf("labels magic number is: %u\n", labelMagicNumber);
    printf("number of labels is: %u\n", numberOfLabels);

    if (numberOfItems != numberOfLabels) {
        fprintf(stderr, "Asserzione fallita: number of items (%u) != number of labels (%u)\n", 
                numberOfItems, numberOfLabels);
        exit(EXIT_FAILURE);
    }

    Sample *head = NULL;
    Sample *last = NULL;
    uint32_t numPixels = nRows * nCols;

    for(uint32_t i = 0; i < numberOfItems; i++) {
        Sample *newSample = xmalloc(sizeof(Sample));
        newSample->next = NULL;

        unsigned char labelByte;
        if (fread(&labelByte, 1, 1, labelF) != 1) {
            fprintf(stderr, "Errore nella lettura della label all'indice %u\n", i);
            exit(EXIT_FAILURE);
        }

        // One-Hot Encoding per le label: j == number ? 1 : 0
        for (int j = 0; j < 10; j++) {
            newSample->label[j] = (j == labelByte) ? 1 : 0;
        }

        for (uint32_t p = 0; p < numPixels; p++) {
            unsigned char pixel;
            fread(&pixel, 1, 1, dataF);
            newSample->originalImage[p] = (int)pixel;
        }

        if (head == NULL) {
            head = newSample;
        } else {
            last->next = newSample;
        }
        last = newSample;
    }

    fclose(dataF);
    fclose(labelF);

    return head;
}

void normalizeImages(Sample *head) {
    Sample *curr = head;
    while(curr != NULL) {
        normalizeImage(curr);
        curr = curr->next;
    }
}

void freeSamples(Sample **head) {
    Sample *curr = *head;
    while (curr != NULL) {
        Sample *next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;
}

void printSamples(Sample *head) {
    Sample *curr = head;
    while(curr != NULL) {
        printf("Label: ");
        for(int i = 0; i < 10; i++) {
            printf("%d", curr->label[i]);
        }
        printf("\n\n");
        for(int row = 0; row < 28; row++) {
            for(int column = 0; column < 28; column++) {
                printf("%d ", curr->originalImage[(row + 1) * column]);
            }
            printf("\n");
        }
        printf("\n\n");
        curr = curr ->next;
    }
}

