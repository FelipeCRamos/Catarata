#include "read.h"

Img *readImage(char *filepath)
{
	FILE *image;
	char buffer[16];
	Img *img; // class of the original image

	int max_rgb;
	char strippedFilepath[strlen(filepath)];

	// strip folder name from the filepath variable
	short m = strlen(filepath);
	short n = 0;
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

	// allocating memory for the image
	img = (Img *) calloc(1, sizeof(Img));
	if (!img) {
		fprintf(stderr, "Can't allocate memory (error reading '%s').\n", strippedFilepath);
		free(img);
		return NULL;
	}

	// opening the image for reading
	image = fopen(filepath, "r");
	if (!image) {
		fprintf(stderr, "Can't open image '%s'.\n", strippedFilepath);
		free(img);
		return NULL; 
	}else{
		printf("Sucess! '%s' has been loaded.\n", strippedFilepath);
	}

	// reading image format
	if (!fgets(buffer, sizeof(buffer), image)) {
		perror("Error reading image format.");
		fclose(image);
		free(img);
		return NULL; 
	}
	buffer[strlen(buffer)] = 0;
	buffer[strlen(buffer) - 1] = '\0';

	// checking image format
	if (buffer[0] != 'P' || buffer[1] != '3') {
		fprintf(stderr, "Wrong image format (should be 'P3'). Error reading '%s'.\n", strippedFilepath);
		fclose(image);
		free(img);
		return NULL; 
	} else {
		printf("The image format is '%s'.\n", buffer);
	}

	// looking for comments
	char c;
	c = getc(image);
	while (c == '#') {
		while (getc(image) != '\n') {
			c = getc(image);
			ungetc(c, image);
		}
	}
	ungetc(c, image);

	// reading height and width
	if (!fscanf(image, "%i %i\n", &img->width, &img->height)) {
		fprintf(stderr, "Invalid image size (error reading '%s').\n", strippedFilepath);
		fclose(image);
		free(img);
		return NULL;
	} else {
		printf("Dimensions identified (W x H): %ix%i pixels.\n", img->width, img->height);
	}
	
	// check the max RGB size allowed fo the image
	if (fscanf(image, "%i", &max_rgb) != 1) {
		fprintf(stderr, "Invalid max RGB value.\n");
	}

	// allocating the size of the pixel matrix
	img->pixels = (Pixel **) calloc(img->height, sizeof(Pixel *));
	for (int i = 0; i < img->height; ++i) {
		img->pixels[i] = (Pixel *) calloc(img->width, sizeof(Pixel));
	}

	// check if the pixel matrix is null
	if (!img->pixels) {
		fprintf(stderr, "Couldn't allocate the pixel matrix (error reading '%s').\n", strippedFilepath);
		fclose(image);
		free(img);
		return NULL;
	}

	// Starting the pixel mapping
	/*
		Little explanation:
			For each 3 lines, we get a rgb(r, g, b), that gets us one pixel.
			Each <Width> pixels, we get a horizontal line
			When we've got <Height> lines, we get the final image.

			There shoud be $width times $height pixels.
	*/
	int loaded_pixels = 0;
	for(int i = 0; i < img->height; ++i) {
		for(int j = 0; j < img->width; ++j) {
			fscanf(image, "%i\n%i\n%i\n", &img->pixels[i][j].r, &img->pixels[i][j].g, &img->pixels[i][j].b);
			loaded_pixels++;
			// if you want to see it for yourself in action, uncomment the next line
			// printf("rgb(%i,%i,%i)\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);
		}
	}

	// check if the number of pixels loaded equals to the number of real pixels.
	if(!(loaded_pixels == img->height * img->width)) {
		fprintf(stderr, "Couldn't load correcly the pixel matrix (should be '%i' pixels, instead, got '%i').\n", img->height * img->width, loaded_pixels);
		fclose(image);
		free(img);
		return NULL;
	} else {
		printf("Correctly loaded %i pixels.\n", loaded_pixels);
	}
	
	printf("Finished reading image...\n");
	// Saving info for posterior work
	strcpy(img->filepath, filepath);
	// printf("%s\n", img->filepath);
	fclose(image);
	return img;
}
