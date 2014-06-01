all: Threadville

Threadville:
	gcc -g main.c UI/ui.c UI/events.c Tarea.c Rutas.c Threadville.c -o Threadville `pkg-config --cflags --libs gtk+-2.0` -lX11 -lglut -lGLU -lGL -lm -lXext
	
NoUI:
	gcc -g Tarea.c Rutas.c Threadville.c -o NoUI `pkg-config --cflags --libs gtk+-2.0` -lX11 -lglut -lGLU -lGL -lm -lXext

clean:
	rm -rf *.o Threadville NoUI
