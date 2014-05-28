#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#define N 714

struct ruta{
	int nodo;
	struct ruta *sig;
} typedef ruta; 

struct automovil{
	pthread_t hilo;
	int viajes;
	//destinos
	int destino[2];
	int posicion;
	int color;
} typedef automovil;

void etiquetar(char*, int);

void avanzar(automovil*);
