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

	printf("The image was toned to its greyscale.\n");

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
					if ( ((i-2+k) >= 0 && (j-2+l) >= 0) && (i+2+k < img->height && j+2+k < img->width) ) {
						filter += img->pixels[i-2+k][j-2+l].r * gauss[k][l]/(double) 159;
						// printf("filter executed\n");
					}
				}
			}

			img->pixels[i][j].r = filter;
			img->pixels[i][j].g = filter;
			img->pixels[i][j].b = filter;
		}
	}

	printf("The image was succesfully blurred.\n");

	return img;
}

Img *sobelFilter(Img *img)
{
	int sobelX[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
	int sobelY[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
	double filterX;
	double filterY;

	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {
			// this will get each pixel of img->**pixels
			// each pixel will be on the "0" on either matrix (sobelX[1][1] and
			// sobelY[1][1]
			
			// sobelX and sobelY covolution
			filterX = 0;
			filterY = 0;
			for (int k = 0; k < 3; ++k) {
				for (int l = 0; l < 3; ++l) {
					if ( ((i-1+k) >= 0 && (j-1+k) >= 0) && ((i+1+k) < img->height && (j+1+k) < img->width) ) {
						filterX += img->pixels[i-1+k][j-1+l].r * sobelX[k][l];
						filterY += img->pixels[i-1+k][j-1+l].r * sobelY[k][l];
					}
				}
			}

			if (sqrt(filterX*filterX + filterY*filterY) > 25) {
				img->pixels[i][j].r = 255;
				img->pixels[i][j].g = 255;
				img->pixels[i][j].b = 255;
			} else {
				img->pixels[i][j].r = sqrt(filterX*filterX + filterY*filterY);
				img->pixels[i][j].g = sqrt(filterX*filterX + filterY*filterY);
				img->pixels[i][j].b = sqrt(filterX*filterX + filterY*filterY);
			}
		}
	}
	
	return img;
}
// TODO
