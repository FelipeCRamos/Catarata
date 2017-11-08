#include "process.h"

Img *grayscale(Img *img){
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
	int filter = 0;
	FILE *log;
	log = fopen("log.txt", "w");
	for(int i=0; i < img->height; i++){
		for(int j=0; j < img->width; j++){
			// this will get each pixel of img->**pixels
			// each pixel will be the "15" on the matrix (gauss[3][3])
			for(int k = 0; k < 5; k++){
				for(int l = 0; l < 5; l++){
					if(i-(k-2) >= 0 && j-(l-2) >= 0){
					filter += (img->pixels[i-(k-2)][j-(l-2)].r + img->pixels[i-(k-2)][j-(l-2)].g + img->pixels[i-(k-2)][j-(l-2)].b) * gauss[k][l];
					// printf("img->pixels[H:%i][W:%i] | rgb(%i,%i,%i) | mapped to guass[%i][%i] (%i)\n", i-(k-2), j-(l-2), img->pixels[i-(k-2)][j-(l-2)].r,img->pixels[i-(k-2)][j-(l-2)].g,img->pixels[i-(k-2)][j-(l-2)].b,k, l, gauss[k][l]);
					fprintf(log ,"img->pixels[H:%i][W:%i] | rgb(%i,%i,%i) | mapped to guass[%i][%i] (%i)\n", i-(k-2), j-(l-2), img->pixels[i-(k-2)][j-(l-2)].r,img->pixels[i-(k-2)][j-(l-2)].g,img->pixels[i-(k-2)][j-(l-2)].b,k, l, gauss[k][l]);

					// printf("foi\n");
					}
				}
			}
			printf("- - - - - - - -\n");
			fprintf(log, "- - - - - - - - - -\n");
			img->pixels[i][j].r = filter;
		}
	}

	return img;
}

// TODO