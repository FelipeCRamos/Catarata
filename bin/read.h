#ifndef READ_H
#define READ_H

#include <stdlib.h>

typedef struct Pixel_t{
	int r; // red
	int g; // green
	int b; // blue
} Pixel;

void readImage(FILE *image, int *height, int *width);

#endif
