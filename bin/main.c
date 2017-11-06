#include <stdio.h>
#include <stdlib.h>
#include "read.h"

int main(int argc, char const *argv[])
{
	FILE *image;
	image = fopen("../res/Catarata.ppm", "r");

  if (image == NULL) perror("Error opening file");

	readImage("../red/Catarata.ppm");

  fclose(image);
	return 0;
}
