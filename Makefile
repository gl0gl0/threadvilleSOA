all: Threadville

Threadville:
	gcc -g Floyd.c Threadville.c -o Threadville `pkg-config --cflags --libs gtk+-2.0` -lX11 -lglut -lGLU -lGL -lm -lXext
	
clean:
	rm -rf *.o Threadville
