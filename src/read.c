#include "read.h"

#define DEBUG 0

Img *readPPM(char *filepath)
{
  puts("\e[1mReading the input image...\e[0m\n");
  FILE *image;
  char buffer[16];
  ushort height, width;
  Img *img; // class of the original image

  uchar max_rgb;
  char *strippedFilepath = stripFilepath(filepath);

  // opening the image for reading
  image = fopen(filepath, "r");
  if (!image)
  {
    fprintf(stderr, "Can't open image '%s'.\n", strippedFilepath);
    perror(filepath);
    exit(1);
  }
  else
  {
    printf("Sucess! '%s' has been loaded.\n", strippedFilepath);
  }

  // reading image format
  if (!fgets(buffer, sizeof(buffer), image))
  {
    perror("Error reading image format.");
    fclose(image);
    return NULL;
  }
  buffer[strlen(buffer)] = 0;
  buffer[strlen(buffer) - 1] = '\0';

  // checking image format
  if (buffer[0] != 'P' || buffer[1] != '3')
  {
    fprintf(stderr, "Wrong image format (should be 'P3'). Error reading '%s'.\n", strippedFilepath);
    fclose(image);
    return NULL;
  }
  else
  {
    printf("The image format is '%s'.\n", buffer);
  }

  // looking for comments
  char c;
  c = getc(image);
  while (c == '#')
  {
    while (getc(image) != '\n')
    {
      c = getc(image);
      ungetc(c, image);
    }
  }
  ungetc(c, image);

  // reading height and width
  if (!fscanf(image, "%hu %hu\n", &width, &height))
  {
    fprintf(stderr, "Invalid image size (error reading '%s').\n", strippedFilepath);
    fclose(image);
    return NULL;
  }
  else
  {
    printf("Dimensions identified (W x H): %ix%i pixels.\n", width, height);
  }

  // check the max RGB size allowed fo the image
  if (fscanf(image, "%hhu", &max_rgb) != 1)
  {
    fprintf(stderr, "Invalid max RGB value.\n");
  }

  // allocating memory for the image
  img = createImg(height, width, max_rgb);
  if (!img)
  {
    fprintf(stderr, "Can't allocate memory (error reading '%s').\n", strippedFilepath);
    freeImg(img);
    fclose(image);
    return NULL;
  }

  // check if the pixel matrix is null
  if (!img->pixels)
  {
    fprintf(stderr, "Couldn't allocate the pixel matrix (error reading '%s').\n", strippedFilepath);
    fclose(image);
    freeImg(img);
    return NULL;
  }

  // Starting the pixel mapping
  /*
		Little explanation:
			For each 3 lines, we get a rgb(r, g, b), that gets us one pixel.
			Each <Width> pixels, we get a horizontal line
			When we've got <Height> lines, we get the final image.

			There shoud be $width times $height pixels.
	*/
  int loaded_pixels = 0;
  for (int i = 0; i < img->height; ++i)
  {
    for (int j = 0; j < img->width; ++j)
    {
      fscanf(image, "%hhu\n%hhu\n%hhu\n", &img->pixels[i][j].r, &img->pixels[i][j].g, &img->pixels[i][j].b);
      ++loaded_pixels;
      // if you want to see it for yourself in action, uncomment the next line
      // printf("rgb(%i,%i,%i)\n", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);
    }
  }

  // check if the number of pixels loaded equals to the number of real pixels.
  if (!(loaded_pixels == img->height * img->width))
  {
    fprintf(stderr, "Couldn't load correcly the pixel matrix (should be '%i' pixels, instead, got '%i').\n", img->height * img->width, loaded_pixels);
    fclose(image);
    freeImg(img);
    return NULL;
  }
  else
  {
    printf("Correctly loaded %i pixels.\n", loaded_pixels);
  }

  puts("\n\e[1mFinished reading image...\e[0m");

  fclose(image);
  free(strippedFilepath);
  return img;
}

ImgBin *readPBM(char *filepath)
{
  puts("\e[1mReading the binary image...\e[0m\n");
  FILE *image;
  char buffer[16];
  ushort height, width;
  ImgBin *img; // class of the original image

  // uchar max_rgb; // not needed, because pbm does not have it
  char *strippedFilepath = stripFilepath(filepath);

  // opening the image for reading
  image = fopen(filepath, "r");
  if (!image)
  {
    fprintf(stderr, "Can't open image '%s'.\n", strippedFilepath);
    perror(filepath);
    exit(1);
  }
  else
  {
    printf("Sucess! '%s' has been loaded.\n", strippedFilepath);
  }

  // reading image format
  if (!fgets(buffer, sizeof(buffer), image))
  {
    perror("Error reading image format.");
    fclose(image);
    return NULL;
  }
  buffer[strlen(buffer)] = 0;
  buffer[strlen(buffer) - 1] = '\0';

  // checking image format
  if (buffer[0] != 'P' || buffer[1] != '1')
  {
    fprintf(stderr, "Wrong image format (should be 'P1'). Error reading '%s'.\n", strippedFilepath);
    fclose(image);
    return NULL;
  }
  else
  {
    printf("The image format is '%s'.\n", buffer);
  }

  // looking for comments
  char c;
  c = getc(image);
  while (c == '#')
  {
    while (getc(image) != '\n')
    {
      c = getc(image);
      ungetc(c, image);
    }
  }
  ungetc(c, image);

  // reading height and width
  if (!fscanf(image, "%hu %hu\n", &width, &height))
  {
    fprintf(stderr, "Invalid image size (error reading '%s').\n", strippedFilepath);
    fclose(image);
    return NULL;
  }
  else
  {
    printf("Dimensions identified (W x H): %ix%i pixels.\n", width, height);
  }

  // allocating memory for the image
  img = createImgBin(height, width);
  if (!img)
  {
    fprintf(stderr, "Can't allocate memory (error reading '%s').\n", strippedFilepath);
    freeImgBin(img);
    fclose(image);
    return NULL;
  }

  // check if the pixel matrix is null
  if (!img->pixels)
  {
    fprintf(stderr, "Couldn't allocate the pixel matrix (error reading '%s').\n", strippedFilepath);
    fclose(image);
    freeImgBin(img);
    return NULL;
  }

  // Starting the pixel mapping
  /*
		Little explanation:
			Each line will give us that row, each pixel will be a number followed with \s
			Each <Width> pixels, we get a horizontal line
			When we've got <Height> lines, we get the final image.

			There shoud be $width times $height pixels.
	*/
  int loaded_pixels = 0;
  int temp_pixel;
  for (int i = 0; i < img->height; ++i)
  {
    for (int j = 0; j < img->width; ++j)
    {
      fscanf(image, "%i", &temp_pixel);
      if (temp_pixel >= 0 && temp_pixel <= 1)
      {
        img->pixels[i][j] = temp_pixel;
      }
      ++loaded_pixels;
      // if you want to see it for yourself in action, uncomment the next line
      // printf("pixel(%i)\n", img->pixels[i][j]);
    }
  }

  // check if the number of pixels loaded equals to the number of real pixels.
  if (!(loaded_pixels == img->height * img->width))
  {
    fprintf(stderr, "Couldn't load correcly the pixel matrix (should be '%i' pixels, instead, got '%i').\n", img->height * img->width, loaded_pixels);
    fclose(image);
    freeImgBin(img);
    return NULL;
  }
  else
  {
    printf("Correctly loaded %i pixels.\n", loaded_pixels);
  }

  printf("\n\e[1mFinished reading the binary image...\e[0m\n");

  fclose(image);
  free(strippedFilepath);
  return img;
}
