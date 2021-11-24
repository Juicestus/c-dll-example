#!/bin/sh
# generate .o files that can be linked together in a dynamic library
cc -c -fPIC func1.c
cc -c -fPIC func2.c
#link together in dynamic library
cc -o libfunc.so -shared -fPIC func1.o func2.o

