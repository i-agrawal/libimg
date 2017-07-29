ACLOCAL_AMFLAGS=-I m4

lib_LTLIBRARIES=libimg.la
libimg_la_SOURCES=img.c img.h
libimg_la_LDFLAGS=-version-info 0:0:0

bin_PROGRAMS=test
test_SOURCES=test.c
test_LDADD=libimg.la $(LIBS)
