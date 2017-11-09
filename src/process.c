#include "process.h"

Img *greyscale(Img *img)
{
	unsigned int toned;
	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {
			toned = (img->pixels[i][j].r*0.3 + img->pixels[i][j].g*0.59 + img->pixels[i][j].b*0.11);
			img->pixels[i][j].r = toned;
			img->pixels[i][j].g = toned;
			img->pixels[i][j].b = toned;
		}
	}
	printf("Greyscale filter applied with sucess\n");
	return img;
}

Img *gaussianFilter(Img *img)
{
	int gauss[5][5] = {{2, 4, 5, 4, 2}, {4, 9, 12, 9, 4}, {5, 12, 15, 12, 5}, {4, 9, 12, 9, 4}, {2, 4, 5, 4, 2}};
	double filter;

	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			// this will get each pixel of img->**pixels
			// each pixel will be the "15" on the matrix (gauss[2][2])

			filter = 0;
			for (int k = 0; k < 5; ++k) {
				for (int l = 0; l < 5; ++l) {
					if (((i-2+k) >= 0 && (j-2+l) >= 0) && (i+2+k < img->height && j+2+k < img->width)) {
						filter += img->pixels[i-2+k][j-2+l].r * gauss[k][l]/(double)159;
						// printf("filter executed\n");
					}
				}
			}

			img->pixels[i][j].r = filter;
			img->pixels[i][j].g = filter;
			img->pixels[i][j].b = filter;
		}
	}
	printf("Gaussian filter applied with sucess\n");
	return img;
}

Img *sobelFilter(Img *img, int orient){
	int xKernel[3][3] = {{1, 0, -1},{1, 0, -1},{1, 0, -1}}; // horizontal sobel-operator
	int yKernel[3][3] = {{1, 1, 1},{0, 0, 0},{-1, -1, -1}}; // vertical sobel-operator
	Img *conv;
	conv = (Img *) calloc(1, sizeof(Img));
	if (!img) {
		// fprintf(stderr, "Can't allocate memory (error reading '%s')\n", strippedFilepath);
		free(img);
		return NULL;
	}
	conv->pixels = (Pixel **) calloc(img->height, sizeof(Pixel *));
	for (int i = 0; i < img->height; ++i) {
		conv->pixels[i] = (Pixel *) calloc(img->width, sizeof(Pixel));
	}


	double aux;
	double filter;
	double power;
	
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {

			filter = 0;
			for (int k = 0; k < 3; ++k) {
				for (int l = 0; l < 3; ++l) {
					if (((i-1+k) >= 0 && (j-1+l) >= 0) && (i+1+k < img->height && j+1+k < img->width)) {
						power = 1;
						if(orient == 0){
							aux = img->pixels[i-1+k][j-1+l].r * xKernel[k][l]/power;
						}
						if(orient == 1){
							aux = img->pixels[i-1+k][j-1+l].r * yKernel[k][l]/power;
						}
						if(aux >= MAX_RGB){
							filter += MAX_RGB;
						}else{
							filter += aux;	
						}
						
					}
				}
			}

			conv->pixels[i][j].r = filter;
			conv->pixels[i][j].g = filter;
			conv->pixels[i][j].b = filter;
		}
	}
	conv->width = img->width;
	conv->height = img->height;
	strcpy(conv->filepath, img->filepath);
	
	if(orient == 0){
		return sobelFilter(conv, 1);
	}
	else{
		if(orient == 1){
			printf("Sobel filter applied with sucess\n");
			return conv;
		}
	}
}

// TODO
