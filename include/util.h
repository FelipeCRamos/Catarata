#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


#define DEBUGGER(fmt, ...)																									 \
	do { 																																			 \
		if (DEBUG) {																														 \
			fprintf(stderr, "\e[1m\x1b[34mDEBUG\x1b[0m\e[0m \e[1m%s:%i:%s():\e[0m ", __FILE__, __LINE__, __func__); 	 \
			fprintf(stderr, fmt,	__VA_ARGS__); 																	 \
		} 																																			 \
	} while (0)

#define MAX_RGB 255
#define ushort unsigned short
#define uchar unsigned char
#define uint unsigned int

typedef struct Pixel_t
{
	uchar r; // red
	uchar g; // green
	uchar b; // blue
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

// Exclusives to Hough Method
typedef struct Circles_t
{
	int count;
	int ***accumulator;
} Circles;

/* 
	When hough finishes his job, will return a CirclesPos Matrix
	made of circles.
	Each circle haves a xPos (center on axis x), an yPos (center on axis y)
	and a ratio.
*/

typedef struct Center_t
{
	int x;
	int y;
	int r;
} Center;

typedef struct Box_t
{
	int xCenter, yCenter;
	int radius;
} Box;

typedef struct Iris_t
{
	int x, y, rad;
} Iris;

// eof

void checkArgs(int argc, char *argv[], char *filepath, char *format, char *diagFile);

char *stripFilepath(char *filepath);

char *outFilepath(char *folder, char *filename, char *toCat, char *format);

Pixel **allocatePixel(ushort height, ushort width);

bool **allocateBinPixel(ushort height, ushort width);

int ***allocateCircle(ushort height, ushort width, int ratio);

Img *createImg(ushort height, ushort width, uchar max_rgb);

ImgBin *createImgBin(ushort height, ushort width);

Circles *createCircles(ushort height, ushort width, int ratio);

ImgBin *convertImg(Img *original);

void freeImg(Img *img);

void freeImgBin(ImgBin *img);

// Funcs for Hough Method
double *preCalcCos();
double *preCalcSin();
Center *createCenter(int x, int y, int r);
Box *createBox(int xCenter, int yCenter, int radius);
Iris *createIris(int x, int y, int rad);

#endif
