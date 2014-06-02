#include "Threadville.h"

void recorrer(void* carro){
	automovil* a;
	a = (automovil*) carro;
	dibujar(a->posicion);
	int siguiente;
	while (a->posicion != a->destino[1]){
		siguiente =	avanzar(a);
		if (!Threadville[siguiente]){
			pthread_mutex_lock(&lock);
			Threadville[siguiente] = 1;
			Threadville[a->posicion] = 0;
			a->posicion = siguiente;
			dibujar(a->posicion);
			usleep(33000);
			pthread_mutex_unlock(&lock);
		}
		//dibujar(a->posicion);
		usleep(1000);
	}
	Threadville[a->posicion] = 0;
	pthread_mutex_unlock(&lock);
}

void dibujar(int pos){
	point posCanvas;
	posCanvas = toCanvas(pos);
	printf("%d,%d\t", posCanvas.x, posCanvas.y);
	//etiquetar(pos);
	gdk_threads_enter();
	//drawCar(posCanvas.x, posCanvas.y, 18, 18);
    gdk_threads_leave();
}


void generarCarro(automovil* a){
	int r;
	r = rand() % 714;
	a->posicion = a->destino[0] = 56;	//7 161 319 473
	r = rand() % 714;
	a->destino[1] = 63;				//154 0 466 312
	printf("Destinos: ");
	etiquetar(a->destino[0]);
	printf(" - %d: ", a->destino[0]);
	etiquetar(a->destino[1]);
	printf(" - %d: ", a->destino[1]);
	printf("\n");
	pthread_create(&a->hilo, NULL, recorrer, (void *) a);
}

int main(int argc, char* argv){
	int i;
	for (i=0; i<N; i++)
		Threadville[i] = 0;
	init();
	srand(time(NULL));
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);
	for (i=0; i<M; i++){
		autos[i] = (automovil *) malloc(sizeof(automovil));
		autos[i]->color = i;
		generarCarro(autos[i]);
	}
	for (i=0; i<M; i++)
		pthread_join(autos[i]->hilo, NULL);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&lock);
	printf("\n");
	return 0;
}
