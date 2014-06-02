#include "Threadville.h"

void recorrer(void* carro){
	automovil* a;
	a = (automovil*) carro;
	dibujar(-1, a->posicion, a->color);
	int siguiente;
	while(!simular){
		usleep(1000);
		continue;
	}
	while (a->posicion != a->destino[1]){
		siguiente =	avanzar(a);
		if (!Threadville[siguiente]){
			pthread_mutex_lock(&lock);
			Threadville[siguiente] = 1;
			Threadville[a->posicion] = 0;
			int ant;
			ant = a->posicion;
			a->posicion = siguiente;
			dibujar(ant, a->posicion, a->color);
			usleep(a->velocidad);
			pthread_mutex_unlock(&lock);
		}
		usleep(1000);
	}
	Threadville[a->posicion] = 0;
	pthread_mutex_unlock(&lock);
}

void dibujar(int ant, int pos, int color){
	point posCanvas;
	posCanvas = toCanvas(pos);
	point antCanvas;
	if (ant < 0){
		antCanvas.x = -1;
		antCanvas.y = -1;
	}
	else	
		antCanvas = toCanvas(ant);
	printf("%d,%d\t", posCanvas.x, posCanvas.y);
	//etiquetar(pos);
	gdk_threads_enter();
	drawCar(color, antCanvas.x, antCanvas.y, posCanvas.x, posCanvas.y, 18, 18);
    gdk_threads_leave();
}


void generarCarro(automovil* a){
	int r;
	r = rand() % 714;
	a->posicion = a->destino[0] = 9;
	r = rand() % 714;
	a->destino[1] = 152;
	r = rand() % 6 + 1;
	a->color = r;
	a->velocidad = r * 19000;
	printf("Destinos: ");
	etiquetar(a->destino[0]);
	printf(" - %d: ", a->destino[0]);
	etiquetar(a->destino[1]);
	printf(" - %d: ", a->destino[1]);
	printf("\n");
	pthread_create(&a->hilo, NULL, recorrer, (void *) a);
}
