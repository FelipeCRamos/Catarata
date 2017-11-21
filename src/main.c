#include "util.h" // header with things that the entire program needs
#include "read.h" // header with only read things
#include "process.h" // header with only process things
#include "write.h" // header with only write things

// Defines the DEBUG mode on/off (0/1)
#define DEBUG 1

int main(int argc, char *argv[])
{
	char *filepath = (char *) calloc(256, sizeof(char));
	char *format = (char *) calloc(8, sizeof(char));
	char *diagFile = (char *) calloc(256, sizeof(char));
	// test if all the arguments were provided
	checkArgs(argc, argv, filepath, format, diagFile);

	// // little welcome interface I did while bored
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
	// puts("\n - Felipe C. Ramos Filho\n - João Pedro de A. Paula\n\n\n");

	// these are just auxiliary variables
	char *filename = stripFilepath(filepath);
	char *outDir = "test/";

	// these are some testing printf's, maybe they'll get changed
	printf("The image to be analised is '%s'.\n", filename);
	printf("%s's format is '%s'\n", filename, format);
	printf("The diagnosis is in '%s'.\n", diagFile);

	putchar('\n');

	Img *originalImg = readPPM(filepath);
	// TODO different reading and writing functions for different formats
	
	if (!originalImg) {
		perror(filepath);
		exit(1);
	}

	// here we enter on process.c
	puts("\n\e[1mStarted processing the image...\e[0m\n");

	// tone the image to its greyscale
	Img *greyscaled = greyscale(originalImg);

	char *outGrey = outFilepath(outDir, filename, "_grey", format);
	char *strippedGrey = stripFilepath(outGrey);
	if (!greyscaled) {
		fprintf(stderr, "Error writing the greyscaled image to '%s'.\n", strippedGrey);
		freeImg(originalImg);
	} else {
		writePPM(greyscaled, outGrey);
	}
	free(outGrey);
	free(strippedGrey);

	// blur the image with the gaussian filter
	Img *gaussImg = gaussianFilter(greyscaled, 1);

	char *outGauss = outFilepath(outDir, filename, "_gauss", format);
	char *strippedGauss = stripFilepath(outGauss);
	if (!gaussImg) {
		fprintf(stderr, "Error writing the blurred image to '%s'.\n", strippedGauss);
	} else {
		writePPM(gaussImg, outGauss);
	}
	free(outGauss);
	free(strippedGauss);
	
	// apply Sobel's filter to enhance the edges
	Img *sobelImg = sobelFilter(gaussImg, 1);

	char *outSobel = outFilepath(outDir, filename, "_sobel", format);
	char *strippedSobel = stripFilepath(outSobel);
	if (!sobelImg) {
		fprintf(stderr, "Error writing the edge detection image to '%s'.\n", strippedSobel);
	} else {
		writePPM(sobelImg, outSobel);
	}
	free(outSobel);
	free(strippedSobel);

	/** 
	 * Apply threshold to sobelImg with intensity calculated through Otsu's Method
	 * pixels bigger than the threshold will be converted to 255 and smaller than
	 * the threshold will be converted to 0.
	 */
	Img *thresholdImg = otsuMethod(sobelImg);

	putchar('\n');

	char *outThreshold = outFilepath(outDir, filename, "_threshold", "pbm");
	char *strippedThreshold = stripFilepath(outThreshold);
	if (!thresholdImg){
		fprintf(stderr, "Error writing the threshold increase image to '%s'.\n", strippedThreshold);
	} else {
		writePPM_PBM(thresholdImg, outThreshold);
	}
	free(outThreshold);
	free(strippedThreshold);

	houghMethod(convertImg(thresholdImg));

	// Just a test to read/write pbm
	// ImgBin *pbmImage = readPBM("test/Catarata_threshold.pbm");
	// writePBM_PBM(pbmImage, "test/teste.pbm");

	// freeImgBin(pbmImage);
	freeImg(thresholdImg);
	free(filepath);
	free(filename);
	free(format);
	free(diagFile);
	return 0;
}
