#include <stdio.h>
#include <stdlib.h>
#include "read.h"

int main(int argc, char const *argv[])
{
	FILE *image;
	image = fopen("../res/Catarata.ppm", "r");
	int height, width;
	readImage(image, &height, &width);

	return 0;
}
