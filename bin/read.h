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

typedef struct Img_t
{
  int height;
  int width;
  Pixel *pixels;
} Img;

Img *readImage(char *imgName);

#endif
