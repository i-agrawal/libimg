// image abstraction struct
typedef struct {
  unsigned char * data;
  int width;
  int height;
} img;

// create image struct from filename
img * imgread(const char *, int);
