#include "process.h"

Img *greyscale(Img *img){
	unsigned int toned;
	for(int i=0; img->height; i++){
		for(int j=0; j<img->width; j++){
			toned = (img->pixels[i][j].r*0.3 + img->pixels[i][j].g*0.59 + img->pixels[i][j].b*0.11);
			img->pixels[i][j].r = toned;
			img->pixels[i][j].g = toned;
			img->pixels[i][j].b = toned;
		}
	}
	return img;
}

Img *gaussianFilter(Img *img){
	int gauss[5][5] = {{2, 4, 5, 4, 2}, {4, 9, 12, 9, 4}, {5, 12, 15, 12, 5}, {4, 9, 12, 9, 4}, {2, 4, 5, 4, 2}};
	double filter_r,filter_g, filter_b;
	int average;
	FILE *log;
	log = fopen("log.txt", "w");
	for(int i=0; i < 5/*img->height*/; i++){
		for(int j=0; j < 5/*img->width*/; j++){
			// this will get each pixel of img->**pixels
			// each pixel will be the "15" on the matrix (gauss[3][3])
			// printf("#### i: %i, j: %i\n", i, j);
			filter_r = 0;
			filter_g =0;
			filter_b = 0;
			average = 0;
			for(int k = 0; k < 5; k++){
				for(int l = 0; l < 5; l++){
					if(((i-2+k) >= 0 && (j-2+l) >= 0) && (i+2+k <= img->height && j+2+k <= img->width)){
						average++;
						filter_r += img->pixels[i-2+k][j-2+l].r * gauss[k][l]/(double)159;
						printf("img->pixels[%i][%i].r = %i * %lf = %lf\n", i-2+k, j-2+l, img->pixels[i-2+k][j-2+l].r, gauss[k][l]/(double)159, img->pixels[i-2+k][j-2+l].r * gauss[k][l]/(double)159);
						filter_g += img->pixels[i-2+k][j-2+l].g * gauss[k][l]/(double)159;
						printf("img->pixels[%i][%i].g = %i * %lf = %lf\n", i-2+k, j-2+l, img->pixels[i-2+k][j-2+l].g, gauss[k][l]/(double)159, img->pixels[i-2+k][j-2+l].g * gauss[k][l]/(double)159);
						filter_b += img->pixels[i-2+k][j-2+l].b * gauss[k][l]/(double)159;
						printf("img->pixels[%i][%i].b = %i * %lf = %lf\n-----------\n", i-2+k, j-2+l, img->pixels[i-2+k][j-2+l].b, gauss[k][l]/(double)159, img->pixels[i-2+k][j-2+l].b * gauss[k][l]/(double)159);
					}
				}
			}
			img->pixels[i][j].r = filter_r;
			img->pixels[i][j].g = filter_g;
			img->pixels[i][j].b = filter_b;
		}
	}

	return img;
}

// TODO