#include "read.h"

void readImage(char *imgName)
{
  FILE *image;
  char buffer[16];
  Pixel *img;
  ImgHeader header;

  // opening the image for reading
  image = fopen(imgName, "r");
  if (!image) {
    fprintf(stderr, "Can't open image '%s'\n", imgName);
    return; 
  }

  // reading image format
  if (!fgets(buffer, sizeof(buffer), image)) {
    perror("Error reading image format");
    fclose(image);
    return; 
  }

  // checking image format
  if (buffer[0] != 'P' || buffer[1] != '3') {
    fprintf(stderr, "Wrong image format (should be 'P3')\n");
    fclose(image);
    return; 
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
  if (!fscanf(image, "%i %i\n", &header.height, &header.width)) {
    fprintf(stderr, "Invalid image size\n");
    fclose(image);
    return;
  }

  fclose(image);
}
