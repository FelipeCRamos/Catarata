#include "util.h" // header with things that the entire program needs
#include "read.h" // header with only read things
#include "process.h" // header with only process things
#include "write.h" // header with only write things

int main(int argc, char const *argv[])
{
	// uncomment this for the interface
	// puts("     ---------------------------------------------------------------------");
	// puts("    |  _     _  _______  ___      _______  _______  __   __  _______  __  |");
	// puts("    | | | _ | ||       ||   |    |       ||       ||  |_|  ||       ||  | |");
	// puts("    | | || || ||    ___||   |    |       ||   _   ||       ||    ___||  | |");
	// puts("    | |       ||   |___ |   |    |       ||  | |  ||       ||   |___ |  | |");
	// puts("    | |       ||    ___||   |___ |      _||  |_|  ||       ||    ___||__| |");
	// puts("    | |   _   ||   |___ |       ||     |_ |       || ||_|| ||   |___  __  |");
	// puts("    | |__| |__||_______||_______||_______||_______||_|   |_||_______||__| |");
	// puts("    |                                                                     |");
	// puts("     ---------------------------------------------------------------------");
	// puts("___                                                               _             ");
	// puts(" | _   |_|_  _   _ _ |_ _  _ _  _|_   _|. _  _  _  _  _. _   _ _ (_|_    _  _ _ ");
	// puts(" |(_)  |_| )(-  (_(_||_(_|| (_|(_|_  (_||(_|(_)| )(_)_)|_)  _)(_)| |_\\)/(_|| (- ");
	// puts("                                            _/                                  ");
	// puts("\n\n /\\   _|_|_  _  _ _.");
	// puts("/~~\\|_|| | |(_)| _\\.");
	// puts("\n - Felipe C. Ramos\n - João Pedro de A. Paula\n\n\n");

	// if (!strcmp(argv[1], "-i")) {
	// 	printf("The image to be analised is '%s'.\n", argv[2]);
	// }

	for (int i = 0; i < argc; ++i) {
		printf("argv[%i]: %s\n", i, argv[i]);
	}

	FILE *image;
	image = fopen("res/Catarata.ppm", "r");

	if (image == NULL) perror("Error opening file");

	Img *original = readImage("res/Catarata.ppm");

	puts("\nStarted processing the image...\n");

	Img *greyscaled = greyscale(original);
	free(original);
	char *strippedGrey = stripFilepath("res/test/cat_grey.ppm");
	if (!greyscaled) {
		fprintf(stderr, "Error writing the greyscaled image to '%s'.\n", strippedGrey);
		fclose(image);
	} else {
		saveImage(greyscaled, "test/cat_grey.ppm");
	}

	Img *gauss = gaussianFilter(greyscaled, 0);
	free(greyscaled);
	char *strippedGauss = stripFilepath("test/cat_gauss.ppm");
	if (!gauss) {
		fprintf(stderr, "Error writing the blurred image to '%s'.\n", strippedGauss);
		fclose(image);
	} else {
		saveImage(gauss, "test/cat_gauss.ppm");
	}

	Img *sobel = sobelFilter(gauss, 1);
	free(gauss);
	char *strippedSobel = stripFilepath("test/cat_sobel.ppm");
	if (!sobel) {
		fprintf(stderr, "Error writing the edge detection image to '%s'.\n", strippedSobel);
		fclose(image);
	} else {
		saveImage(sobel, "test/cat_sobel.ppm");
	}

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
