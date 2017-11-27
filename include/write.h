#ifndef WRITE_H
#define WRITE_H

#include "util.h"

void writePPM(Img *img, char *filepath);

void writePBM_PBM(ImgBin *img, char *filepath);

void writePPM_PBM(Img *img, char *filepath);

void drawBox(Img *img, char *filepath, Box *box);

void drawIris(Img *img, char *filepath, Iris *box);

#endif
