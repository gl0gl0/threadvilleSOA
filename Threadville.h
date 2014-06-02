#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#define N 714

#define M 1

#define K 6

#define borderwidth 80;

int NOBUSES;

struct ruta{
	int nodo;
	struct ruta *sig;
} typedef ruta; 

struct automovil{
	pthread_t hilo;
	int viajes;
	int* destino;
	int destinoActual;
	int posicion;
	int color;
	unsigned velocidad;
	int tipo;
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

automovil *BusRojo;
automovil *BusVerde;
automovil *BusAzul;
automovil *BusBlanco;
automovil *BusGris;
automovil *BusNegro;
automovil *BusRosa;
automovil *BusCeleste;
automovil *BusNaranja;

int indiceCarro;



void etiquetar(int);

int avanzar(automovil*);

void init();

void llenarMatriz();

void Floyd();

void generarCarro(automovil*);

point toCanvas(int);

void dibujar(int, int, int);

int simular;

int convertToken(char*);
