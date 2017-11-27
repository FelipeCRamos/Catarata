#include "util.h"

#define DEBUG 1

// check if all the arguments were provided
void checkArgs(int argc, char *argv[], char *filepath, char *format, char *diagFile)
{
	if (argc < 3) {
		fprintf(stderr, "usage: ./catarata -i <input-image> -f <input-image-format>"
			 " -o <diagnose-file>\n\n\t-i\tspecify the path to the image to be analised"
			 "\n\t-f\tthe format of the input image\n\t-o\tpath to the diagnosis"
			 " file\n\nExample of usage:\n"
			 "./catarata -i res/Catarata.ppm -f ppm -o diagnosis.txt\n\n");
		exit(1);
	} else if (argc < 7) {
		bool input_bool = false;
		bool format_bool = false;
		bool diagFile_bool = false;
		uchar i = 1;
		while (i < argc) {
			if (!strcmp(argv[i], "-i")) {
				if (i+1 == argc || !strcmp(argv[i+1], "-f") || !strcmp(argv[i+1], "-i")) {
					fprintf(stderr, "usage: ./catarata -i <input-image> -f <input-image-format>"
						 " -o <diagnose-file>\n\n\t-i\tspecify the path to the image to be analised"
						 "\n\t-f\tthe format of the input image\n\t-o\tpath to the diagnosis"
						 " file\n\nExample of usage:\n"
						 "./catarata -i res/Catarata.ppm -f ppm -o diagnosis.txt\n\n");
					exit(1);
				}
				
				filepath = strcpy(filepath, (char *) argv[i+1]);
				input_bool = true;
			}

			if (!strcmp(argv[i], "-f")) {
				if (i+1 == argc || !strcmp(argv[i+1], "-o") || !strcmp(argv[i+1], "-i")) {
					fprintf(stderr, "usage: ./catarata -i <input-image> -f <input-image-format>"
						 " -o <diagnose-file>\n\n\t-i\tspecify the path to the image to be analised"
						 "\n\t-f\tthe format of the input image\n\t-o\tpath to the diagnosis"
						 " file\n\nExample of usage:\n"
						 "./catarata -i res/Catarata.ppm -f ppm -o diagnosis.txt\n\n");
					exit(1);
				}

				format = strcpy(format, (char *) argv[i+1]);
				format_bool = true;
			}

			if (!strcmp(argv[i], "-o")) {
				if (i+1 == argc || !strcmp(argv[i+1], "-f") || !strcmp(argv[i+1], "-i")) {
					fprintf(stderr, "usage: ./catarata -i <input-image> -f <input-image-format>"
						 " -o <diagnose-file>\n\n\t-i\tspecify the path to the image to be analised"
						 "\n\t-f\tthe format of the input image\n\t-o\tpath to the diagnosis"
						 " file\n\nExample of usage:\n"
						 "./catarata -i res/Catarata.ppm -f ppm -o diagnosis.txt\n\n");
					exit(1);
				}

				diagFile = strcpy(diagFile, (char *) argv[i+1]);
				diagFile_bool = true;
			}

			++i;
		}

		if (!input_bool) {
			fprintf(stderr, "Please specify an input image after the -i.\n");
			exit(1);
		}

		if (!format_bool) {
			printf("\n\e[1m\x1b[33mWARNING\e[0m\x1b[0m: No format specified, defaulting to 'ppm'.\n");
			format = realloc(format, 4);
			strcpy(format, "ppm");
		}

		if (!diagFile_bool) {
			printf("\e[1m\x1b[33mWARNING\e[0m\x1b[0m: No diagnosis file specified, defaulting to 'diagnosis.txt'.\n\n");
			diagFile = realloc(diagFile, 14);
			strcpy(diagFile, "diagnosis.txt");
		}

		if (format_bool && argc%2 == 0) {
			fprintf(stderr, "Please specify a format after the -f.\n");
			exit(1);
		} else if (diagFile_bool && argc%2 == 0) {
			fprintf(stderr, "Please specify a diagnose file after the -o.\n");
			exit(1);
		}
	} else if (argc == 7) {
		/* check what are the args passed on to the program and store the args'
		indexes on a variable, so we can access them any time we want */
		for (uchar i = 0; i < argc; ++i) {
			if (!strcmp(argv[i], "-i")) {
				filepath = realloc(filepath, strlen(argv[i+1]) + 1);
				strcpy(filepath, (char *) argv[i+1]);
			} else if (!strcmp(argv[i], "-f")) {
				format = realloc(format, strlen(argv[i+1]) + 1);
				strcpy(format, (char *) argv[i+1]);
			} else if (!strcmp(argv[i], "-o")) {
				diagFile = realloc(diagFile, strlen(argv[i+1]) + 1);
				strcpy(diagFile, (char *) argv[i+1]);
			}
		}
	}
}

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
Pixel **allocatePixel(ushort height, ushort width)
{
	Pixel **pixels = (Pixel **) calloc(height, sizeof(Pixel *));
	for (int i = 0; i < height; ++i) {
		pixels[i] = (Pixel *) calloc(width, sizeof(Pixel));
	}

	return pixels;
}

// this allocates a new bool **
bool **allocateBinPixel(ushort height, ushort width)
{
	bool **pixels = (bool **) calloc(height, sizeof(bool *));
	for (int i = 0; i < height; i++) {
		pixels[i] = (bool *) calloc(width, sizeof(bool));
	}
	return pixels;
}

// this allocates a new circle
int ***allocateCircle(ushort height, ushort width, int ratio)
{
	int ***circles = (int ***) calloc(height, sizeof(int **));
	for (int i = 0; i < height; ++i) {
		circles[i] = (int **) calloc(width, sizeof(int *));
		for (int j = 0; j < width; j++){
			circles[i][j] = (int *) calloc(ratio, sizeof(int));
		}
	}
	return circles;
}

// this allocates a new Img *
Img *createImg(ushort height, ushort width, uchar max_rgb)
{
	Img *newImg = (Img *) calloc(1, sizeof(Img));
	newImg->height = height;
	newImg->width = width;
	newImg->max_rgb = max_rgb;

	newImg->pixels = allocatePixel(height, width);

	return newImg;
}

ImgBin *createImgBin(ushort height, ushort width){
	ImgBin *newImgBin = (ImgBin *) calloc(1, sizeof(ImgBin));
	newImgBin->height = height;
	newImgBin->width = width;

	newImgBin->pixels = allocateBinPixel(height, width);

	return newImgBin;
}

Circles *createCircles(ushort height, ushort width, int ratio)
{
	Circles *newCircles = (Circles *) calloc(1, sizeof(Circles));
	newCircles->count = 0;
	newCircles->accumulator = allocateCircle(height, width, ratio);
	return newCircles;
}

// this converts a ppm image (with rgb) to pbm image (with 0,1)
// its currently designed to recieve a ppm Img with threshold applied already, so the values are or 0, or 255
// * currently not tested *
ImgBin *convertImg(Img *original){
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

// void freeIris(Iris *iris)
// {
// 	for ()
// }

double *preCalcSin(){
	double pi = 3.14;
	double *list = (double *) calloc (360, sizeof(double));
	for(unsigned short int i = 0; i < 360; i++){
		list[i] = sin(pi/180.0*i);
	}
	return(list);
}
double *preCalcCos(){
	double pi = 3.14;
	double *list = (double *) calloc (360, sizeof(double));
	for(unsigned short int i = 0; i < 360; i++){
		list[i] = cos(pi/180.0*i);
	}
	return(list);
}

Center *createCenter(int x, int y, int r){
	Center *center = (Center *) calloc (1, sizeof(Center));
	center->x = x;
	center->y = y;
	center->r = r;
	return(center);
}

Box *createBox(int xCenter, int yCenter, int radius){
	Box *box = (Box *) calloc (1, sizeof(Box));
	box->xCenter = xCenter, box->yCenter = yCenter, box->radius = radius;
	printf("\nDEBUG MESSAGE:\tx: %i y: %i r: %i\n", box->xCenter, box->yCenter, box->radius);
	return(box);
}

Iris *createIris(int x, int y, int rad){
	Iris *iris = (Iris *) calloc (1, sizeof(Iris));
	iris->x = x, iris->y = y, iris->rad = rad;
	return(iris);
}

