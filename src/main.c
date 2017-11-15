#include "util.h" // header with things that the entire program needs
#include "read.h" // header with only read things
#include "process.h" // header with only process things
#include "write.h" // header with only write things

// Defines the DEBUG Mode on/off (0/1)
#define DEBUG 0

int main(int argc, char const *argv[])
{
	// test if all the arguments were provided
	if (argc < 7) {
		fprintf(stderr, "usage: ./catarata -i <input-image> -f <input-image-format>"
			 " -o <diagnose-file>\n\n\t-i\tspecify the path to the image to be analised"
			 "\n\t-f\tthe format of the input image\n\t-o\tpath to the diagnosis"
			 " file\n\nExample of usage:\n"
			 "./catarata -i res/Catarata.ppm -f ppm -o tests/Catarata_Diag.ppm\n\n");
		exit(1);
	}

	// little welcome interface I did while bored
	puts("     ---------------------------------------------------------------------");
	puts("    |  _     _  _______  ___      _______  _______  __   __  _______  __  |");
	puts("    | | | _ | ||       ||   |    |       ||       ||  |_|  ||       ||  | |");
	puts("    | | || || ||    ___||   |    |       ||   _   ||       ||    ___||  | |");
	puts("    | |       ||   |___ |   |    |       ||  | |  ||       ||   |___ |  | |");
	puts("    | |       ||    ___||   |___ |      _||  |_|  ||       ||    ___||__| |");
	puts("    | |   _   ||   |___ |       ||     |_ |       || ||_|| ||   |___  __  |");
	puts("    | |__| |__||_______||_______||_______||_______||_|   |_||_______||__| |");
	puts("    |                                                                     |");
	puts("     ---------------------------------------------------------------------");
	puts("___                                                               _             ");
	puts(" | _   |_|_  _   _ _ |_ _  _ _  _|_   _|. _  _  _  _  _. _   _ _ (_|_    _  _ _ ");
	puts(" |(_)  |_| )(-  (_(_||_(_|| (_|(_|_  (_||(_|(_)| )(_)_)|_)  _)(_)| |_\\)/(_|| (- ");
	puts("                                            _/                                  ");
	puts("\n\n /\\   _|_|_  _  _ _.");
	puts("/~~\\|_|| | |(_)| _\\.");
	puts("\n - Felipe C. Ramos Filho\n - João Pedro de A. Paula\n\n\n");

	/* check what are the args passed on to the program and store the args'
	indexes on a variable, so we can access them any time we want */
	uchar inputIndex;
	uchar formatIndex;
	uchar outputIndex;
	for (uchar i = 0; i < argc; ++i) {
		if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "-o") || !strcmp(argv[i], "-f")) {
			if (!strcmp(argv[i], "-i")) {
				inputIndex = i+1;
			} else if (!strcmp(argv[i], "-f")) {
				formatIndex = i+1;
			} else if (!strcmp(argv[i], "-o")) {
				outputIndex = i+1;
			}
		}
	}

	// these are just auxiliary variables
	char *filepath = (char *) argv[inputIndex];
	char *filename = stripFilepath(filepath);
	char *format = (char *) argv[formatIndex];
	char *diagFile = (char *) argv[outputIndex];
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
	puts("\nStarted processing the image...\n");

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


	// Apply threshold to sobelImg with intensity 35 (pixels bigger than this will be converted to 255, smaller than will be 0);
	Img *thresholdImg = threshold(sobelImg, 30);

	char *outThreshold = outFilepath(outDir, filename, "_threshold2", "pbm");
	char *strippedThreshold = stripFilepath(outThreshold);
	if (!thresholdImg){
		fprintf(stderr, "Error writing the threshold increase image to '%s'.\n", strippedThreshold);
	} else {
		writePBM(thresholdImg, outThreshold);
	}


	freeImg(sobelImg);
	free(filename);
	return 0;
}
