#ifndef LEITURA_H
#define LEITURA_H

#include <stdlib.h>
typedef struct Pixel_t{
	int r; // red
	int g; // green
	int b; // blue
} RGB;

void readImage(FILE *image, int *height, int *weight);

#endif