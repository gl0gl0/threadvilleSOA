threadvilleSOA
==============

To run:

$ gcc -g main.c ui.c -o main `pkg-config --cflags --libs gtk+-2.0` -lX11 -lglut -lGLU -lGL -lm -lXext -lrt
$ ./main