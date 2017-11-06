#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"

int main(int argc, char const *argv[])
{
	FILE *image;
	image = fopen("../res/Catarata.ppm", "r");
	int height, weight;
	readImage(image, &height, &weight);

	return 0;
}