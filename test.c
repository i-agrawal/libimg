#include "img.h"
#include <stdio.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    printf("usage: %s [filepath]\n", argv[0]);
    return 1;
  }

  img * image;
  if (!(image = imgread(argv[1], 0))) {
    printf("unable to read image\n");
    return 0;
  }

  printf("%i, %i\n", image->width, image->height);
  return 0;
}
