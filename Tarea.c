#include "Threadville.h"

void recorrer(void* carro){
	automovil* a;
	a = (automovil*) carro;
	int siguiente;
	int dest;
	while(1){
		a->destinoActual = 1;
	for (dest=0; dest<a->viajes-1; dest++){
		dibujar(-1, a->posicion, a->color);
		while (a->posicion != a->destino[a->destinoActual]){
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
			while(!simular){
				usleep(1000);
				continue;
			}
			usleep(1000);
		}
		usleep(3000000);
		a->posicion = a->destino[a->destinoActual++];
		Threadville[a->posicion] = 0;
		pthread_mutex_unlock(&lock);
	}
	}
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
	//printf("%d,%d\t", posCanvas.x, posCanvas.y);
	//etiquetar(pos);
	gdk_threads_enter();
	drawCar(color, antCanvas.x, antCanvas.y, posCanvas.x, posCanvas.y, 18, 18);
    gdk_threads_leave();
}


void generarCarro(automovil* a){
	printf("Destinos: ");
	int i;
	for (i=0; i<a->viajes; i++){
		etiquetar(a->destino[i]);
		printf(" - %d: ", a->destino[i]);
	}
	printf("\n");
	pthread_create(&a->hilo, NULL, recorrer, (void *) a);
}
