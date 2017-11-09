#include "utils.h" // header with things that the entire program needs
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
	saveImage(greyscaled, "res/tests/cat_grey.ppm");


	Img *gauss = gaussianFilter(greyscaled);
	saveImage(gauss, "res/tests/cat_gauss.ppm");

	Img *sobel = sobelFilter(gauss, 0);
	saveImage(sobel, "res/tests/cat_sobel.ppm");

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
