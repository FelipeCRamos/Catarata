#ifndef PROCESS_H
#define PROCESS_H

#include "utils.h"

Img *greyscale(Img *img);

Img *gaussianFilter(Img *img);

Img *sobelFilter(Img *img, int orient);
// TODO

#endif