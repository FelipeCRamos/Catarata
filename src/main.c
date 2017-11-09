#include "util.h" // header with things that the entire program needs
#include "read.h" // header with only read things
#include "process.h" // header with only process things
#include "write.h" // header with only write things

int main(int argc, char const *argv[])
{
	FILE *image;
	image = fopen("res/Catarata.ppm", "r");

	if (image == NULL) perror("Error opening file");

	Img *original = readImage("res/Catarata.ppm");

	Img *greyscaled = greyscale(original);
	saveImage(greyscaled, "test/cat_grey.ppm");
	char *strippedGrey = stripFilepath("res/test/cat_grey.ppm");
	if (!greyscaled) {
		fprintf(stderr, "Error writing the greyscaled image to '%s'.\n", strippedGrey);
	}

	Img *gauss = gaussianFilter(greyscaled);
	saveImage(gauss, "test/cat_gauss.ppm");
	char *strippedGauss = stripFilepath("test/cat_gauss.ppm");
	if (!gauss) {
		fprintf(stderr, "Error writing the blurred image to '%s'.\n", strippedGauss);
	}

	Img *sobel = sobelFilter(gauss);
	saveImage(sobel, "test/cat_sobel.ppm");
	char *strippedSobel = stripFilepath("test/cat_sobel.ppm");
	if (!sobel) {
		fprintf(stderr, "Error writing the edge detection image to '%s'.\n", strippedSobel);
	}

	// saveImage(gaussianFilter(greyscaled), "../res/tests/Catarata_gauss.ppm");

/* // DEBUG HELPER
	printf("img->height: %i\n", original->height);
	printf("img->filepath: %s\n", original->filepath);
	for (int i = 0; i < original->height; ++i) {
		for (int j = 0; j < original->width; ++j) {
			printf("rgb(%i,%i,%i)\n", original->pixels[i][j].r, original->pixels[i][j].g, original->pixels[i][j].b);
		}
	}
*/
	fclose(image);
	return 0;
}
