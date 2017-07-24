# libimg: image abstraction library

This library provides image format independent interfacing.  
Currently the library is a work in progress.  
Currently supports reading png format, must be linked against libpng.  

Compile the test program using:  
```
    gcc -c -o img.o img.c
    gcc -c -o test.o test.c
    gcc -o test -lpng img.o test.o
```

Simply gives size of image:  
```
    usage: test [file]
```
