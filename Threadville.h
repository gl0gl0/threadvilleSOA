#include <stdio.h>
#include <stdlib.h>

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#define N 714

struct ruta{
	int nodo;
	struct ruta *sig;
} typedef ruta; 

struct automovil{
	int viajes;
	//destinos
	int destino[2];
	ruta* viaje;
	ruta* posicion;
	int velocidad;
	//color
} typedef automovil;

void etiquetar(char*, int);

void hacerRuta(automovil*);
