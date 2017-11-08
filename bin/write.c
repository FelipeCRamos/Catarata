#include "utils.h"
#include "write.h"

void saveImage(Img *image, char path[]){
	FILE *outImage;
	// int toned;
	outImage = fopen(path, "w");
	fprintf(outImage, "P3\n# CREATED BY FELIPE RAMOS & JOAO PEDRO\n");
	fprintf(outImage, "%i %i\n", image->width, image->height);
	fprintf(outImage, "%i\n", MAX_RGB);
	for(int i=0; i<image->height; i++){
		for(int j=0; j<image->width; j++){
			fprintf(outImage, "%i\n%i\n%i\n", image->pixels[i][j].r, image->pixels[i][j].g, image->pixels[i][j].b);
		}
	}
	fclose(outImage);
}