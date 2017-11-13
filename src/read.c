#include "read.h"

Img *readPPM(char *filepath)
{
	puts("Reading the image...\n");
	FILE *image;
	char buffer[16];
	ushort height, width;
	Img *img; // class of the original image

	uchar max_rgb;
	char *strippedFilepath = stripFilepath(filepath);

	// opening the image for reading
	image = fopen(filepath, "r");
	if (!image) {
		fprintf(stderr, "Can't open image '%s'.\n", strippedFilepath);
		perror(filepath);
		exit(1);
	} else{
		printf("Sucess! '%s' has been loaded.\n", strippedFilepath);
	}

	// reading image format
	if (!fgets(buffer, sizeof(buffer), image)) {
		perror("Error reading image format.");
		fclose(image);
		return NULL; 
	}
	buffer[strlen(buffer)] = 0;
	buffer[strlen(buffer) - 1] = '\0';

	// checking image format
	if (buffer[0] != 'P' || buffer[1] != '3') {
		fprintf(stderr, "Wrong image format (should be 'P3'). Error reading '%s'.\n", strippedFilepath);
		fclose(image);
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
	if (!fscanf(image, "%hu %hu\n", &width, &height)) {
		fprintf(stderr, "Invalid image size (error reading '%s').\n", strippedFilepath);
		fclose(image);
		return NULL;
	} else {
		printf("Dimensions identified (W x H): %ix%i pixels.\n", width, height);
	}
	
	// allocating memory for the image
	img = createImg(height, width);
	if (!img) {
		fprintf(stderr, "Can't allocate memory (error reading '%s').\n", strippedFilepath);
		freeImg(img);
		fclose(image);
		return NULL;
	}

	// check the max RGB size allowed fo the image
	if (fscanf(image, "%hhu", &max_rgb) != 1) {
		fprintf(stderr, "Invalid max RGB value.\n");
	}
	img->max_rgb = max_rgb;

	// allocating the size of the pixel matrix
	// img->pixels = (Pixel **) calloc(img->height, sizeof(Pixel *));

	// check if the pixel matrix is null
	if (!img->pixels) {
		fprintf(stderr, "Couldn't allocate the pixel matrix (error reading '%s').\n", strippedFilepath);
		fclose(image);
		freeImg(img);
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
			fscanf(image, "%hu\n%hu\n%hu\n", &img->pixels[i][j].r, &img->pixels[i][j].g, &img->pixels[i][j].b);
			++loaded_pixels;
			// if you want to see it for yourself in action, uncomment the next line
			// printf("rgb(%i,%i,%i)\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);
		}
	}

	// check if the number of pixels loaded equals to the number of real pixels.
	if(!(loaded_pixels == img->height * img->width)) {
		fprintf(stderr, "Couldn't load correcly the pixel matrix (should be '%i' pixels, instead, got '%i').\n", img->height * img->width, loaded_pixels);
		fclose(image);
		freeImg(img);
		return NULL;
	} else {
		printf("Correctly loaded %i pixels.\n", loaded_pixels);
	}
	
	printf("\nFinished reading image...\n");

	fclose(image);
	free(strippedFilepath);
	return img;
}
