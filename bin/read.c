#include <stdio.h>
#include <stdlib.h>
#include "read.h"

void readImage(FILE *image, int *height, int *width)
{
	fscanf(image, "%i %i", height, width);
	printf("Altura: %i, Largura: %i\n", *height, *width);
}
