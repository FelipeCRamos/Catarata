#include "util.h"

char *stripFilepath(char *filepath)
{
	char *strippedFilepath = (char *) calloc(strlen(filepath), sizeof(char));

	// strip folder name from the filepath variable
	short m = strlen(filepath);
	short n = 0;
	while (filepath[m] != '/') {
		strippedFilepath[n] = filepath[m];
		--m;
		++n;
	}
	strippedFilepath[n] = '\0';

	// here we have to invert the string because it is reversed (Catarata.ppm is mpp.atarataC)
	for (int i = 0, j = n - 1; i < j; ++i, --j) {
		char aux = strippedFilepath[i];
		strippedFilepath[i] = strippedFilepath[j];
		strippedFilepath[j] = aux;
	}

	return strippedFilepath;
}

Pixel **allocatePixel(int height, int width)
{
	Pixel **pixels = (Pixel **) calloc(height, sizeof(Pixel *));
	for (int i = 0; i < height; ++i) {
		pixels[i] = (Pixel *) calloc(width, sizeof(Pixel));
	}

	return pixels;
}

Img *createImg(int height, int width)
{
	Img *newImg = (Img *) calloc(1, sizeof(Img));
	newImg->height = height;
	newImg->width = width;

	newImg->pixels = allocatePixel(height, width);

	return newImg;
}
