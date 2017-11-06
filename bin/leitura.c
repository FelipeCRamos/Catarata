#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"

void readImage(FILE *image, int *height, int *weight){
	
	fscanf(image, "%i %i", height, weight);
	printf("Altura: %i, Largura: %i\n", *height, *weight);


}
