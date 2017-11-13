#include "write.h"

#define DEBUG 1

void writePPM(Img *img, char *filepath)
{
	FILE *outImage;
	outImage = fopen(filepath, "w");

	if (!outImage) {
		perror(filepath);
	}

	// imagem format and creators comment
	fprintf(outImage, "P3\n# CREATED BY FELIPE RAMOS & JOAO PEDRO\n");

	// width and height of the image
	fprintf(outImage, "%hu %hu\n", img->width, img->height);

	// the maximum rgb value of the image
	fprintf(outImage, "%i\n", img->max_rgb);

	DEBUG_PRINT("img->max_rgb: %i\n", img->max_rgb);

	// writing all of the rgb values of each pixel of the image
	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {
			fprintf(outImage, "%i\n%i\n%i\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);
		}
	}

	fclose(outImage);
}
