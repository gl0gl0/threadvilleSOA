#include "Threadville.h"

automovil* autos[4];

pthread_mutex_t lock;
pthread_cond_t cond;

void loop(void* carro){
	automovil* a;
	a = (automovil*) carro;
	printf("%d_", a->color);
	etiquetar(a->posicion);
	int siguiente;
	while (a->posicion != a->destino[1]){
		siguiente =	avanzar(a);
		if (!Threadville[siguiente]){
			pthread_mutex_lock(&lock);
			Threadville[siguiente] = 1;
			Threadville[a->posicion] = 0;
			a->posicion = siguiente;
			usleep(1400);
			pthread_mutex_unlock(&lock);
		}
		usleep(1400);
		if (siguiente == a->posicion){
			//printf("%d_%d_%d_", a->color, Threadville[siguiente], siguiente);
			printf("%d_", a->color);
			etiquetar(a->posicion);
			//printf("%d ", a->posicion);
		}
	}
	Threadville[a->posicion] = 0;
	pthread_mutex_unlock(&lock);
}


void generarCarro(automovil* a){
	int r;
	r = rand() % 714;
//	if (a->color==0)
	a->posicion = a->destino[0] = r;
//	else
//	a->posicion = a->destino[0] = 7;
	r = rand() % 714;
//	if (a->color==0)
	a->destino[1] = r;
//	else
//	a->destino[1] = (28*5) +7;
	printf("Destinos: ");
	etiquetar(a->destino[0]);
	printf(" - %d: ", a->destino[0]);
	etiquetar(a->destino[1]);
	printf(" - %d: ", a->destino[1]);
	printf("\n");
	pthread_create(&a->hilo, NULL, loop, (void *) a);
}

int main(int argc, char* argv){
	int i;
	for (i=0; i<N; i++)
		Threadville[i] = 0;
	init();
	srand(time(NULL));
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);
	for (i=0; i<2; i++){
		autos[i] = (automovil *) malloc(sizeof(automovil));
		autos[i]->color = i;
		generarCarro(autos[i]);
	}
	for (i=0; i<2; i++)
		pthread_join(autos[i]->hilo, NULL);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&lock);
	printf("\n");
	return 0;
}
