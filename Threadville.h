#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#define N 714

#define M 1

#define borderwidth 80;

struct ruta{
	int nodo;
	struct ruta *sig;
} typedef ruta; 

struct automovil{
	pthread_t hilo;
	int viajes;
	int destino[2];
	int posicion;
	int color;
	int anterior;
} typedef automovil;

struct point{
	int x;
	int y;
} typedef point;

int Sucesores[N][N];
int Threadville[N];

pthread_mutex_t lock;
pthread_cond_t cond;

automovil* autos[M];



void etiquetar(int);

int avanzar(automovil*);

void init();

void llenarMatriz();

void Floyd();

void generarCarro(automovil*);

point toCanvas(int);

void dibujar(int);
