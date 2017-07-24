#include "img.h"
#include <stdio.h>
#include <stdlib.h>
#include "png.h"

img * imgread(const char * filename, int options) {
  // open image file
  FILE * imgfile;
  if (!(imgfile = fopen(filename, "r"))) {
    fprintf(stderr, "unable to open file\n");
    return 0;
  }

  // get image header
  unsigned char header[8];
  if (fread(header, 1, 8, imgfile) != 8) {
    fprintf(stderr, "unable to read header\n");
    fclose(imgfile);
    return 0;
  }

  // if png read into 8-bit RGBA array
  if (!png_sig_cmp(header, 0, 8)) {
    png_structp png_ptr;
    // create png struct
    if (!(png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0))) {
      fclose(imgfile);
      fprintf(stderr, "unable to create png struct\n");
      return 0;
    }

    // create png info struct
    png_infop info_ptr;
    if (!(info_ptr = png_create_info_struct(png_ptr))) {
      png_destroy_read_struct(&png_ptr, 0, 0);
      fclose(imgfile);
      fprintf(stderr, "unable to create info struct\n");
      return 0;
    }

    // set longjmp for error checking
    if (setjmp(png_jmpbuf(png_ptr))) {
      png_destroy_read_struct(&png_ptr, &info_ptr, 0);
      fclose(imgfile);
      fprintf(stderr, "unable to setjmp\n");
      return 0;
    }

    // initialize png with our file
    png_init_io(png_ptr, imgfile);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    // get width, height, color type, and bit depth
    png_uint_32 width, height;
    int color_t, bit_d;
    if (!png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_d, &color_t, 0, 0, 0)) {
      png_destroy_read_struct(&png_ptr, &info_ptr, 0);
      fclose(imgfile);
      fprintf(stderr, "unable to get ihdr\n");
      return 0;
    }

    // convert image to 8-bit RGBA
    // 16-bit depth > 8-bit depth
    if (bit_d == 16) {
      png_set_strip_16(png_ptr);
    }
    // palette > rgb
    if (color_t == PNG_COLOR_TYPE_PALETTE) {
      png_set_palette_to_rgb(png_ptr);
    }
    // gray {1,2,4}-bit depth > 8-bit depth
    if (color_t == PNG_COLOR_TYPE_GRAY && bit_d < 8) {
      png_set_expand_gray_1_2_4_to_8(png_ptr);
    }
    // if gray set to rgb
    if (color_t == PNG_COLOR_TYPE_GRAY || color_t == PNG_COLOR_TYPE_GRAY_ALPHA) {
      png_set_gray_to_rgb(png_ptr);
    }
    // make transparency an alpha channel
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
      png_set_tRNS_to_alpha(png_ptr);
    }
    // if no original alpha channel
    if (color_t == PNG_COLOR_TYPE_RGB || color_t == PNG_COLOR_TYPE_GRAY || color_t == PNG_COLOR_TYPE_PALETTE) {
      png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
    }
    // update png to 8-bit RGBA
    png_read_update_info(png_ptr, info_ptr);

    // create buffer for image data
    unsigned char * data;
    png_uint_32 rowbytes;
    rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    if (!(data = malloc(rowbytes * height))) {
      png_destroy_read_struct(&png_ptr, &info_ptr, 0);
      fclose(imgfile);
      fprintf(stderr, "unable to allocate memory\n");
      return 0;
    }

    // create a bunch of pointers to each row of data
    int i;
    png_bytep * row_pointers;
    row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);
    for (i = 0; i != height; i++) {
      row_pointers[i] = data + i * rowbytes;
    }

    // read image data
    png_read_image(png_ptr, row_pointers);
    // read post image data
    png_read_end(png_ptr, info_ptr);
    // we no longer need png, info, nor the file
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    fclose(imgfile);

    img result = {data, width, height};
    img * res_ptr = (img *) malloc(sizeof(img));
    *res_ptr = result;
    return res_ptr;
  }
  else {
    fprintf(stderr, "file format not supported\n");
    fclose(imgfile);
    return 0;
  }
}
