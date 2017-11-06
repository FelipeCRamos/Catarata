#include "read.h"

Img *readImage(char *imgName)
{
  FILE *image;
  char buffer[16];
  Pixel **pixels;
  Img *img;
  int max_rgb;
  char strippedImgName[strlen(imgName)];

  // strip folder name from the imgName variable
  short m = strlen(imgName);
  short n = 0;
  while (imgName[m] != '/') {
    strippedImgName[n] = imgName[m];
    printf("%s", strippedImgName);
    printf("m: %i, n: %i\n", m, n);
    --m;
    ++n;
  }
  strippedImgName[n] = '\0';

  // here we have to invert the string because it is reversed (Catarata is atarataC)
  for (int i = 0, j = n - 1; i < j; ++i, --j) {
    char aux = strippedImgName[i];
    strippedImgName[i] = strippedImgName[j];
    strippedImgName[j] = aux;
  }

  // allocating memory for the image
  img = (Img *) calloc(1, sizeof(Img));
  if (!img) {
    fprintf(stderr, "Can't allocate memory (error reading '%s')\n", strippedImgName);
    free(img);
    return NULL;
  }

  // opening the image for reading
  image = fopen(imgName, "r");
  if (!image) {
    fprintf(stderr, "Can't open image '%s'\n", strippedImgName);
    free(img);
    return NULL; 
  }

  // reading image format
  if (!fgets(buffer, sizeof(buffer), image)) {
    perror("Error reading image format");
    fclose(image);
    free(img);
    return NULL; 
  }

  // checking image format
  if (buffer[0] != 'P' || buffer[1] != '3') {
    fprintf(stderr, "Wrong image format (should be 'P3'). Error reading '%s'\n", strippedImgName);
    fclose(image);
    free(img);
    return NULL; 
  }

  // looking for comments
  char c;
  c = getc(image);
  while (c == '#') {
    while (getc(image) != '\n') {
      c = getc(image);
      ungetc(c, image);
    }
  }
  ungetc(c, image);

  // reading height and width
  if (!fscanf(image, "%i %i\n", &img->height, &img->width)) {
    fprintf(stderr, "Invalid image size (error reading '%s'\n", strippedImgName);
    fclose(image);
    free(img);
    return NULL;
  }
  
  // check the max RGB size allowed fo the image
  if (fscanf(image, "%i", &max_rgb) != 1) {
    fprintf(stderr, "Invalid max RGB value\n");
  }

  // allocating the size of the pixel matrix
  pixels = (Pixel **) calloc(img->height, sizeof(Pixel *));
  for (int i = 0; i < img->height; ++i) {
    pixels[i] = (Pixel *) calloc(img->width, sizeof(Pixel));
  }

  fclose(image);
  return img;
}
