#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * Alloca memoria in modo sicuro.
 * @param size Numero di byte da allocare.
 * @return Un puntatore generico alla memoria allocata.
 */
void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Errore fatale: impossibile allocare %zu byte.\n", size);
        exit(EXIT_FAILURE);
    }

    return ptr;
}

FILE *xfopen(const char *path, const char *mode) {
    FILE *f = fopen(path, mode);
    if (f == NULL) {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    return f;
}

