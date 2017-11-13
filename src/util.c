#include "util.h"

// remove the filepath from the string
char *stripFilepath(char *filepath)
{
	// if the argument is the file itself, return it
	if (!strstr(filepath, "/")) {
		return filepath;
	}

	char *strippedFilepath = (char *) calloc(strlen(filepath), sizeof(char));

	// strip folder name from the filepath
	ushort m = strlen(filepath);
	ushort n = 0;
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

// generate the output filepath
char *outFilepath(char *folder, char *filename, char *toCat, char *format)
{ 
	char *outFilepath;
	outFilepath = (char *) calloc(strlen(folder) + strlen(filename) + strlen(toCat) + strlen(format), sizeof(char));

	strcpy(outFilepath, folder);

	// strip image format from the filename
	uchar i = 0;
	uchar j = strlen(outFilepath);
	while (filename[i] != '.') {
		outFilepath[j] = filename[i];
		++i;
		++j;
	}

	strcat(outFilepath, toCat);
	// add the '.' for the format
	outFilepath[strlen(outFilepath)] = '.';
	strcat(outFilepath, format);

	return outFilepath;
}

// this allocates a new Pixel **
Pixel **allocatePixel(int height, int width)
{
	Pixel **pixels = (Pixel **) calloc(height, sizeof(Pixel *));
	for (int i = 0; i < height; ++i) {
		pixels[i] = (Pixel *) calloc(width, sizeof(Pixel));
	}

	return pixels;
}

// this allocates a new Img *
Img *createImg(int height, int width)
{
	Img *newImg = (Img *) calloc(1, sizeof(Img));
	newImg->height = height;
	newImg->width = width;
	// TODO work on the max_rgb value
	newImg->max_rgb = 255;

	newImg->pixels = allocatePixel(height, width);

	return newImg;
}

void freeImg(Img *img)
{
	for (ushort i = 0; i < img->height; ++i) {
		free(img->pixels[i]);
	}
	free(img->pixels);

	free(img);
}
