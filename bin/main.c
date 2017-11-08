#include "general.h" // lib with things that the entire program needs
#include "read.h" // lib with only read things
#include "process.h" // lib with only process things

int main(int argc, char const *argv[])
{
	FILE *image;
	image = fopen("../res/Catarata.ppm", "r");

  	if (image == NULL) perror("Error opening file");

	Img *original = readImage("../res/Catarata.ppm");

/* // DEBUG HELPER
	printf("img->height: %i\n", original->height);
	printf("img->filepath: %s\n", original->filepath);
	for(int i=0; i<original->height; i++){
		for(int j=0; j<original->width; j++){
			printf("rgb(%i,%i,%i)\n", original->pixels[i][j].r, original->pixels[i][j].g, original->pixels[i][j].b);
		}
	}
*/
  	fclose(image);
	return 0;
}
