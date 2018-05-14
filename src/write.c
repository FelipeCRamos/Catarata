#include "write.h"

#define DEBUG 0

void writePPM(Img *img, char *filepath)
{
  FILE *outImage;
  outImage = fopen(filepath, "w");

  if (!outImage)
  {
    perror(filepath);
  }

  // imagem format and creators comment
  fprintf(outImage, "P3\n# CREATED BY FELIPE RAMOS & JOAO PEDRO\n");

  // width and height of the image
  fprintf(outImage, "%hu %hu\n", img->width, img->height);

  // the maximum rgb value of the image
  fprintf(outImage, "%i\n", img->max_rgb);

  // writing all of the rgb values of each pixel of the image
  for (int i = 0; i < img->height; ++i)
  {
    for (int j = 0; j < img->width; ++j)
    {
      fprintf(outImage, "%i\n%i\n%i\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);
    }
  }

  fclose(outImage);
}

// a write pbm func that recieves a ImgBin *
void writePBM_PBM(ImgBin *img, char *filepath)
{
  FILE *outImage;
  outImage = fopen(filepath, "w");
  int *pixel = (int *)calloc(1, sizeof(bool));

  if (!outImage)
  {
    perror(filepath);
  }

  // imagem format and creators comments
  fprintf(outImage, "P1\n# CREATED BY FELIPE RAMOS & JOÃO PEDRO\n");

  // width and height of the image
  fprintf(outImage, "%hu %hu\n", img->width, img->height);

  // writing all of the binary values of each pixel of the image
  for (int i = 0; i < img->height; i++)
  {
    for (int j = 0; j < img->width; j++)
    {
      fprintf(outImage, "%i ", *pixel);
      if (*pixel >= 0 && *pixel <= 1)
      {
        img->pixels[i][j] = *pixel;
      }
      else
      {
        fprintf(stderr, "Value %i is not a bool (it shoud be, it's a PBM)", *pixel);
      }
    }
    fprintf(outImage, "\n");
  }

  fclose(outImage);
  free(pixel);
}

// a write pbm func that recieves a Img *
void writePPM_PBM(Img *img, char *filepath)
{
  FILE *outImage;
  outImage = fopen(filepath, "w");
  int pixel = 0;

  if (!outImage)
  {
    perror(filepath);
  }

  // imagem format and creators comments
  fprintf(outImage, "P1\n# CREATED BY FELIPE RAMOS & JOÃO PEDRO\n");

  // width and height of the image
  fprintf(outImage, "%hu %hu\n", img->width, img->height);

  // writing all of the binary values of each pixel of the image
  for (int i = 0; i < img->height; i++)
  {
    for (int j = 0; j < img->width; j++)
    {
      if (img->pixels[i][j].r == img->max_rgb)
      {
        pixel = 0;
      }
      else
      {
        pixel = 1;
      }
      fprintf(outImage, "%i ", pixel);
    }
    fprintf(outImage, "\n");
  }
  fclose(outImage);
}

void drawIris(Img *img, char *filepath, Iris *iris)
{
  FILE *outImage;
  outImage = fopen(filepath, "w");

  if (!outImage)
  {
    perror(filepath);
  }

  // imagem format and creators comment
  fprintf(outImage, "P3\n# CREATED BY FELIPE RAMOS & JOAO PEDRO\n");

  // width and height of the image
  fprintf(outImage, "%hu %hu\n", img->width, img->height);

  // the maximum rgb value of the image
  fprintf(outImage, "%i\n", img->max_rgb);

  // making calculations
  int xS = iris->x - iris->rad, yS = iris->y - iris->rad, xE = iris->x + iris->rad, yE = iris->y + iris->rad;

  for (int i = 0; i < img->height; ++i)
  {
    for (int j = 0; j < img->width; ++j)
    {

      /* FORMULAS */
      /* 
				TO GET THE OUTLINE OF THE CIRCLE:
					If the (x,y) satisfies the condition:
						y = sin(degree) * radius + Cy
						x = cos(degree) * radius + Cx
						
						i = sin(degree) * iris->rad + iris->y
						j = cos(degree) * iris->rad + iris->x
					
					Then, it should be an outline;

				TO GET THE INSIDE CONTENT OF A CIRCLE:
					If the (x,y) are inside:
						(x - radius) and (x + radius) and (y - radius) and (y + radius)
						&&
						((pow(i - iris->y, 2) + pow(j - iris->x, 2)) <= iris->rad * iris->rad)
					Then, it's a content from the circle;
			*/

      // ENABLE THE FOLLOWING LINES TO GET THE CONTENT FROM A CIRCLE
      if (((i >= yS && j >= xS) && (i <= yE && j <= xE)) && ((pow(i - iris->y, 2) + pow(j - iris->x, 2)) <= iris->rad * iris->rad))
      {
        int r, g, b;
        r = 255;
        if (10 + img->pixels[i][j].g > 255)
          g = 255;
        else
          g = 10 + img->pixels[i][j].g;
        if (10 + img->pixels[i][j].b > 255)
          b = 255;
        else
          b = 10 + img->pixels[i][j].b;

        fprintf(outImage, "%i\n%i\n%i\n", r, g, b);
      }
      else
      {
        fprintf(outImage, "%i\n%i\n%i\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);
      }

      // double *sin = preCalcSin();
      // double *cos = preCalcCos();

      // ENABLE THE FOLLOWING LINES TO GET JUST THE OUTLINE FROM A CIRCLE
      // if (/**/(i >= yS && j >= xS) && (i <= yE && j <= xE)/**/) {

      // 	fprintf(outImage, "%i\n%i\n%i\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);

      // 	for(int t = 0; t < 360; t+=2){
      // 		if(i == (int)sin[t] * iris->rad + iris->y && j == (int)cos[t] * iris->rad + iris->x){
      // 			fprintf(outImage, "%i\n%i\n%i\n", 255, 10, 10);
      // 		}

      // 	}
      // 	// fprintf(outImage, "%i\n%i\n%i\n", 255, 10, 10);
      // } else {
      // 	fprintf(outImage, "%i\n%i\n%i\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);
      // }
    }
  }

  fclose(outImage);
}

void segIris(Img *img, char *filepath, Iris *iris)
{
  FILE *outImage;
  outImage = fopen(filepath, "w");

  if (!outImage)
  {
    perror(filepath);
  }

  // imagem format and creators comment
  fprintf(outImage, "P3\n# CREATED BY FELIPE RAMOS & JOAO PEDRO\n");

  // width and height of the image
  fprintf(outImage, "%hu %hu\n", img->width, img->height);

  // the maximum rgb value of the image
  fprintf(outImage, "%i\n", img->max_rgb);

  // making calculations
  int xS = iris->x - iris->rad, yS = iris->y - iris->rad, xE = iris->x + iris->rad, yE = iris->y + iris->rad;

  // writing all of the rgb values of each pixel of the image
  for (int i = 0; i < img->height; ++i)
  {
    for (int j = 0; j < img->width; ++j)
    {
      /* FORMULAS */
      /* 
				TO GET THE OUTLINE OF THE CIRCLE:
					If the (x,y) satisfies the condition:
						y = sin(degree) * radius + Cy
						x = cos(degree) * radius + Cx
						
						i = sin(degree) * iris->rad + iris->y
						j = cos(degree) * iris->rad + iris->x
					
					Then, it should be an outline;

				TO GET THE INSIDE CONTENT OF A CIRCLE:
					If the (x,y) are inside:
						(x - radius) and (x + radius) and (y - radius) and (y + radius)
						&&
						((pow(i - iris->y, 2) + pow(j - iris->x, 2)) <= iris->rad * iris->rad)
					Then, it's a content from the circle;
			*/

      // ENABLE THE FOLLOWING LINES TO GET THE CONTENT FROM A CIRCLE
      if (((i >= yS && j >= xS) && (i <= yE && j <= xE)) && ((pow(i - iris->y, 2) + pow(j - iris->x, 2)) <= iris->rad * iris->rad))
      {
        fprintf(outImage, "%i\n%i\n%i\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);
      }
      else
      {
        fprintf(outImage, "%i\n%i\n%i\n", 0, 0, 0);
      }

      // double *sin = preCalcSin();
      // double *cos = preCalcCos();

      // ENABLE THE FOLLOWING LINES TO GET JUST THE OUTLINE FROM A CIRCLE
      // if (/**/(i >= yS && j >= xS) && (i <= yE && j <= xE)/**/) {

      // 	fprintf(outImage, "%i\n%i\n%i\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);

      // 	for(int t = 0; t < 360; t+=2){
      // 		if(i == (int)sin[t] * iris->rad + iris->y && j == (int)cos[t] * iris->rad + iris->x){
      // 			fprintf(outImage, "%i\n%i\n%i\n", 255, 10, 10);
      // 		}

      // 	}
      // 	// fprintf(outImage, "%i\n%i\n%i\n", 255, 10, 10);
      // } else {
      // 	fprintf(outImage, "%i\n%i\n%i\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);
      // }
    }
  }

  fclose(outImage);
}