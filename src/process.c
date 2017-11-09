#include "process.h"

double min(double a, double b)
{
	return a > b ? b : a;
}

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

Img *gaussianFilter(Img *oringinalImg)
{
	Img *gaussImg = createImg(oringinalImg->height, oringinalImg->width);

	int gauss[5][5] = {{1, 4, 7, 4, 1}, {4, 16, 26, 16, 4}, {7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
	double filter;
	double normalizationFactor = 273;

	for (int i = 0; i < gaussImg->height; i++) {
		for (int j = 0; j < gaussImg->width; j++) {
			// this will get each pixel of img->**pixels
			// each pixel will be the "15" on the matrix (gauss[2][2])

			filter = 0;
			for (int k = 0; k < 5; ++k) {
				for (int l = 0; l < 5; ++l) {
					if ( ((i-2+k) >= 0 && (j-2+l) >= 0) && (i+2+k < gaussImg->height && j+2+k < gaussImg->width) ) {
						filter += oringinalImg->pixels[i-2+k][j-2+l].r * gauss[k][l]/normalizationFactor;
						// printf("filter executed\n");
					}
				}
			}

			gaussImg->pixels[i][j].r = filter;
			gaussImg->pixels[i][j].g = filter;
			gaussImg->pixels[i][j].b = filter;
		}
	}

	printf("The image was succesfully blurred.\n");

	return gaussImg;
}

Img *sobelFilter(Img *originalImg)
{
	Img *sobelImg = createImg(originalImg->height, originalImg->width);

	int sobel_x[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
	int sobel_y[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
	int filter_x;
	int filter_y;

	for (int i = 0; i < sobelImg->height; ++i) {
		for (int j = 0; j < sobelImg->width; ++j) {
			// this will get each pixel of img->**pixels
			// each pixel will be on the "0" on either matrix (sobel_x[1][1] and
			// sobel_y[1][1]
			
			// sobel_x and sobel_y covolution
			filter_x = 0;
			filter_y = 0;
			for (int k = 0; k < 3; ++k) {
				for (int l = 0; l < 3; ++l) {
					// this tests if the pixel is on a border
					if ( (i == 0 || j == 0) || (i == sobelImg->height - 1 || j == sobelImg->width - 1) ) {
						// if it is, then its value is 0
						filter_x += 0;
						filter_y += 0;
					} else {
						// else, we multiply
						filter_x += originalImg->pixels[i-1+k][j-1+l].r * sobel_x[k][l];
						filter_y += originalImg->pixels[i-1+k][j-1+l].r * sobel_y[k][l];
					}
				}
			}

			// here we test if the magnitude is greater then the MAX_RGB value
			if (sqrt(filter_x*filter_x + filter_y*filter_y) > MAX_RGB) {
				sobelImg->pixels[i][j].r = MAX_RGB;
				sobelImg->pixels[i][j].g = MAX_RGB;
				sobelImg->pixels[i][j].b = MAX_RGB;
			} else {
				sobelImg->pixels[i][j].r = sqrt(filter_x*filter_x + filter_y*filter_y);
				sobelImg->pixels[i][j].g = sqrt(filter_x*filter_x + filter_y*filter_y);
				sobelImg->pixels[i][j].b = sqrt(filter_x*filter_x + filter_y*filter_y);
			}
		}
	}
	
	return sobelImg;
}

// TODO
