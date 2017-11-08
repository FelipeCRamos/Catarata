#include "process.h"

Img *grayscale(Img *image){
	unsigned static int toned;
	for(int i=0; i<image->height; i++){
		for(int j=0; j<image->width; j++){
			toned = (image->pixels[i][j].r*0.3 + image->pixels[i][j].g*0.59 + image->pixels[i][j].b*0.11);
			image->pixels[i][j].r = toned;
			image->pixels[i][j].g = toned;
			image->pixels[i][j].b = toned;
		}
	}
	return image;
}

// TODO