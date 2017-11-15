#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


#define DEBUG_PRINT(fmt, ...)																								 \
	do { 																																			 \
		if (DEBUG) {																														 \
			fprintf(stderr, "DEBUG %s:%i:%s(): ", __FILE__, __LINE__, __func__); 	 \
			fprintf(stderr, fmt,	__VA_ARGS__); 																	 \
		} 																																			 \
	} while (0)

#define MAX_RGB 255
#define ushort unsigned short
#define uchar unsigned char

typedef struct Pixel_t
{
	ushort r; // red
	ushort g; // green
	ushort b; // blue
} Pixel;

typedef struct Img_t
{
	// char filepath[50];
	uchar max_rgb;
	ushort height;
	ushort width;
	Pixel **pixels;
} Img;

typedef struct ImgBin_t
{
	ushort height;
	ushort width;
	bool **pixels;
} ImgBin;

char *stripFilepath(char *filepath);

char *outFilepath(char *folder, char *filename, char *toCat, char *format);

Pixel **allocatePixel(int height, int width);

bool **allocateBinPixel(int height, int width);

Img *createImg(int height, int width, uchar max_rgb);

ImgBin *createImgBin(int height, int width);

ImgBin *convertImg(Img *original);

void freeImg(Img *img);

void freeImgBin(ImgBin *img);

#endif
