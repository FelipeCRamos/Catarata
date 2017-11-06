#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RGB 255

typedef struct Pixel_t
{
	int r; // red
	int g; // green
	int b; // blue
} Pixel;

typedef struct ImgHeader_t
{
  int height;
  int width;
  Pixel *pixels;
} ImgHeader;

char *stripFileName(char *filename);

void readImage(char *imgName);

#endif
