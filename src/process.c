#include "process.h"

Img *greyscale(Img *img)
{
	ushort toned;
	for (ushort i = 0; i < img->height; ++i) {
		for (ushort j = 0; j < img->width; ++j) {
			toned = (img->pixels[i][j].r*0.3 + img->pixels[i][j].g*0.59 + img->pixels[i][j].b*0.11);
			img->pixels[i][j].r = toned;
			img->pixels[i][j].g = toned;
			img->pixels[i][j].b = toned;
		}
	}

	printf("The image was toned to its greyscale.\n");

	return img;
}

Img *gaussianFilter(Img *originalImg, uchar limit)
{
	if (limit <= 0) {
		fprintf(stderr, "Can't execute %i times the Gaussian filter, please give a valid number (greater than 0).\n", limit);
		return NULL;
	} 

	Img *gaussImg = createImg(originalImg->height, originalImg->width);

	uchar gauss[7][7] = {{1, 1, 2, 2, 2, 1, 1}, {1, 3, 4, 5, 4, 3, 1}, {2, 4, 7, 8, 7, 4, 2}, {2, 5, 8, 10, 8, 5, 2}, {2, 4, 7, 8, 7, 4, 2}, {1, 3, 4, 5, 4, 3, 1}, {1, 1, 2, 2, 2, 1, 1}};
	float filter;
	float normalizationFactor = 170;
	static uchar count = 0;

	// uncomment these two lines if you want to use a 5x5 Gaussian kernel
	// int gauss[5][5] = {{2, 4, 5, 4, 2}, {4, 9, 12, 9, 4}, {5, 12, 12, 12, 5}, {4, 9, 12, 9, 4}, {2, 4, 5, 4, 2}};
	// double normalizationFactor = 159;

	for (ushort i = 0; i < gaussImg->height; i++) {
		for (ushort j = 0; j < gaussImg->width; j++) {
			// this will get each pixel of img->**pixels
			// each pixel will be the "15" on the matrix (gauss[2][2])

			filter = 0;
			for (uchar k = 0; k < 7; ++k) {
				for (uchar l = 0; l < 7; ++l) {
					if ( ((i-3+k) >= 0 && (j-3+l) >= 0) && (i+3 < gaussImg->height && j+3 < gaussImg->width) ) {
						filter += originalImg->pixels[i-3+k][j-3+l].r * gauss[k][l]/normalizationFactor;
						// printf("filter executed\n");
					}
				}
			}

			gaussImg->pixels[i][j].r = filter;
			gaussImg->pixels[i][j].g = filter;
			gaussImg->pixels[i][j].b = filter;
		}
	}

	if (!gaussImg) {
		fprintf(stderr, "Error while blurring. Resulting image is NULL.\n");
		free(gaussImg);
		free(originalImg);
	} else {
		if (count == 0) {
			printf("The image was succesfully blurred %i time.\n", count + 1);
			++count;
		} else {
			printf("The image was succesfully blurred %i times.\n", count + 1);
			++count;
		}
	}

	if (limit > 1) {
		gaussImg = gaussianFilter(gaussImg, limit - 1);
	} else if (limit == 1) {
		return gaussImg;
	}

	return gaussImg;
}

Img *sobelFilter(Img *originalImg, uchar limit)
{
	if (limit <= 0) {
		fprintf(stderr, "Can't execute %i times the Sobel filter, please give a valid number (greater than 0).\n", limit);
		return NULL;
	} 

	Img *sobelImg = createImg(originalImg->height, originalImg->width);

	int sobel_x[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
	int sobel_y[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
	int filter_x;
	int filter_y;
	static uchar count = 0;

	for (ushort i = 0; i < sobelImg->height; ++i) {
		for (ushort j = 0; j < sobelImg->width; ++j) {
			/* this will get each pixel of img->**pixels; each pixel will be on the "0"
			 * on either matrix (sobel_x[1][1] and sobel_y[1][1] */
			
			// sobel_x and sobel_y covolution
			filter_x = 0;
			filter_y = 0;
			for (uchar k = 0; k < 3; ++k) {
				for (uchar l = 0; l < 3; ++l) {
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
			// TODO replace MAX_RGB with originalImg->max_rgb
			if (sqrt(filter_x*filter_x + filter_y*filter_y) > MAX_RGB) {
				sobelImg->pixels[i][j].r = originalImg->max_rgb;
				sobelImg->pixels[i][j].g = originalImg->max_rgb;
				sobelImg->pixels[i][j].b = originalImg->max_rgb;
			} else {
				sobelImg->pixels[i][j].r = sqrt(filter_x*filter_x + filter_y*filter_y);
				sobelImg->pixels[i][j].g = sqrt(filter_x*filter_x + filter_y*filter_y);
				sobelImg->pixels[i][j].b = sqrt(filter_x*filter_x + filter_y*filter_y);
			}
		}
	}
	
	if (!sobelImg) {
		fprintf(stderr, "Error while aplying Sobel's Filter. Resulting image is NULL.\n");
		free(sobelImg);
		free(originalImg);
	} else {
		if (count == 0) {
			printf("Sobel's filter was successfully applied %i time.\n", count + 1);
			++count;
		} else {
			printf("Sobel's filter was successfully applied %i times.\n", count + 1);
			++count;
		}
		// printf("Sobel's filter was successfully applied.\n");
	}

	if (limit > 1) {
		sobelImg = sobelFilter(sobelImg, limit - 1);
	} else if (limit == 1) {
		return sobelImg;
	}

	return sobelImg;
}

// TODO
