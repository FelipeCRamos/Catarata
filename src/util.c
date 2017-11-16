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

// this allocates a new bool **
bool **allocateBinPixel(int height, int width)
{
	bool **pixels = (bool **) calloc(height, sizeof(bool *));
	for (int i = 0; i < height; i++) {
		pixels[i] = (bool *) calloc(width, sizeof(bool));
	}
	return pixels;
}

// this allocates a new Img *
Img *createImg(int height, int width, uchar max_rgb)
{
	Img *newImg = (Img *) calloc(1, sizeof(Img));
	newImg->height = height;
	newImg->width = width;
	newImg->max_rgb = max_rgb;

	newImg->pixels = allocatePixel(height, width);

	return newImg;
}

ImgBin *createImgBin(int height, int width){
	ImgBin *newImgBin = (ImgBin *) calloc(1, sizeof(ImgBin));
	newImgBin->height = height;
	newImgBin->width = width;

	newImgBin->pixels = allocateBinPixel(height, width);

	return newImgBin;
}

// this converts a ppm image (with rgb) to pbm image (with 0,1)
// its currently designed to recieve a ppm Img with threshold applied already, so the values are or 0, or 255
// * currently not tested *
ImgBin *convertPPtoPB(Img *original){
	ImgBin *converted = (ImgBin *) calloc(1, sizeof(ImgBin));
	converted->height = original->height;
	converted->width = original->width;

	converted->pixels = allocateBinPixel(converted->height, converted->width);
	for (int i = 0; i < original->height; i++) {
		for (int j = 0; j < original->width; j++) {
			if (original->pixels[i][j].r == original->max_rgb) {
				converted->pixels[i][j] = 0;
			} else {
				converted->pixels[i][j] = 1;
			}
		}
	}
	return converted;
}

void freeImg(Img *img)
{
	for (ushort i = 0; i < img->height; ++i) {
		free(img->pixels[i]);
	}
	free(img->pixels);

	free(img);
}

void freeImgBin(ImgBin *img)
{
	for (ushort i = 0; i < img->height; i++) {
		free(img->pixels[i]);
	}
	free(img->pixels);
	free(img);
}