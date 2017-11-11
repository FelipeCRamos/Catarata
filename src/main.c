#include "util.h" // header with things that the entire program needs
#include "read.h" // header with only read things
#include "process.h" // header with only process things
#include "write.h" // header with only write things

int main(int argc, char const *argv[])
{
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
	puts("\n - Felipe C. Ramos\n - João Pedro de A. Paula\n\n\n");

	if (argc < 7) {
		// TODO: verification of which flag is missing
	}

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
	
	// this is on read.c
	Img *original = readPPM(filepath);

	if (!original) {
		perror(filepath);
		exit(1);
	}

	// here we enter on process.c
	puts("\nStarted processing the image...\n");

	// tone the image to its greyscale
	Img *greyscaled = greyscale(original);

	char *outGrey = outFilepath(outDir, filename, "_grey", format);
	char *strippedGrey = stripFilepath(outGrey);
	if (!greyscaled) {
		fprintf(stderr, "Error writing the greyscaled image to '%s'.\n", strippedGrey);
		free(original);
	} else {
		writePPM(greyscaled, outGrey);
	}

	// blur the image with the gaussian filter
	Img *gauss = gaussianFilter(greyscaled, 1);

	char *outGauss = outFilepath(outDir, filename, "_gauss", format);
	char *strippedGauss = stripFilepath(outGauss);
	if (!gauss) {
		fprintf(stderr, "Error writing the blurred image to '%s'.\n", strippedGauss);
	} else {
		writePPM(gauss, outGauss);
	}
	
	// apply Sobel's filter to enhance the edges
	Img *sobel = sobelFilter(gauss, 1);
	free(gauss);

	char *outSobel = outFilepath(outDir, filename, "_sobel", format);
	char *strippedSobel = stripFilepath(outSobel);
	if (!sobel) {
		fprintf(stderr, "Error writing the edge detection image to '%s'.\n", strippedSobel);
	} else {
		writePPM(sobel, outSobel);
	}

	free(original);
	return 0;
}
