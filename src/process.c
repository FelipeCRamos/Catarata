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

	return img;
}

Img *gaussianFilter(Img *img)
{
	int gauss[5][5] = {{2, 4, 5, 4, 2}, {4, 9, 12, 9, 4}, {5, 12, 15, 12, 5}, {4, 9, 12, 9, 4}, {2, 4, 5, 4, 2}};
	double filter;
	int average;
	int pixel = 0;
	int final = 0;
	// FILE *log;
	// log = fopen("log.txt", "w");
	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {
			// this will get each pixel of img->**pixels
			// each pixel will be the "15" on the matrix (gauss[3][3])
			// printf("#### i: %i, j: %i\n", i, j);

			filter = 0;
			average = 0;
			for (int k = 0; k < 5; ++k) {
				for (int l = 0; l < 5; ++l) {
					if (((i-2+k) >= 0 && (j-2+l) >= 0) && (i+2+k < img->height && j+2+k < img->width)) {
						average++;
						filter += img->pixels[i-2+k][j-2+l].r * gauss[k][l]/(double) 159;
						// printf("filter executed\n");
					}
				}
			}

			printf("Pixel %i processed.\n", pixel++);
			final += average;
			// printf("Filter: %lf\n", filter);
			img->pixels[i][j].r = filter;
			img->pixels[i][j].g = filter;
			img->pixels[i][j].b = filter;
		}
	}

	printf("filter executed %i times.\n", final);

	return img;
}

// TODO
