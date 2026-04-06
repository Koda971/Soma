#ifndef UTILS_H                                                             
#define UTILS_H

#include <stdio.h>

void *xmalloc(size_t size);
FILE *xfopen(const char *path, const char *mode);

#endif
