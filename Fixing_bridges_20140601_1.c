#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <sys/time.h>

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#define ESTE_OESTE 'E'
#define OESTE_ESTE 'O'
#define CARRO 0
#define AMBULANCIA 1
#define FALSE 0
#define TRUE 1

// Estructura para los vehiculos
typedef struct Vehiculo {
    unsigned int id;
    unsigned short prioridad; // 0: Ambulancia, 1: normal
    float velocidad;
    char sentido;
    unsigned short prioridad_creado;
    unsigned int entro;
    unsigned int cruzo;
    unsigned int salio;
} Vehiculo;

// Estructura comparti0da del puente
typedef struct {
    char sentido;
    unsigned int largo;
    unsigned short k;
    unsigned short tiempo_semaforo;
    pthread_mutex_t lock;
    pthread_cond_t vacio;
    pthread_cond_t disponible_salida;
    pthread_cond_t semaforo_disponible;
    int contador;
    unsigned short permiso_entrada;
    Vehiculo *capacidad[6];
} Puente;

typedef struct{
    unsigned int sentido;
    pthread_mutex_t mutex;
    pthread_cond_t ocupado;
    sem_t cambio_Sentido;
} semGlobal_t;

semGlobal_t semGlobal;

/* Variables Globales */

/* Modalidad de ejecución
    0: Auto regulado
    1: Con semáforo
    2: Con oficiales de tránsito
*/
unsigned short modalidad;
float v_promedio;
unsigned int media_vehiculos;
sem_t semaforo;
unsigned int verde;
int t_semaforo;
int carros = 0;
int prioridad_global;
int posicion_cola = 1;

int salidos;
int maximo_salidos;

Puente puente;

void timestamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    char buff[100];
    time_t now = time (0);
    strftime (buff, 100, "%H:%M:%S", localtime (&now));
    //UNCOMMENT: printf ("%s . %d", buff, tv.tv_usec);
}

int asignarParametros(){
    //Leer parametros desde archivo
    char lectura[80];
    FILE *archivo = fopen("parametros.txt", "r");
    if(archivo == NULL)
                return -1;
    //Largo del puente
    fscanf(archivo, " %s\n", lectura);
    puente.largo = atoi(lectura);
    //Media de vehiculos
    fscanf(archivo, " %s\n", lectura);
    media_vehiculos = atoi(lectura);
    //Velocidad promedio
    fscanf(archivo, " %s\n", lectura);
    v_promedio = atoi(lectura);
    //Tiempo semaforo
    fscanf(archivo, " %s\n", lectura);
    t_semaforo = atoi(lectura);

    return 0;
}


/*void activarSemaforo()
{
    while(1)
    {
        sem_wait(&semaforo);
        int tiemporecorrido = t_semaforo * 100;
        //printf("En el puente hay %d cantidad de carros\n", puente.contador);
        verde = verde == 0 ? 1 : 0;
        //Este 0 y Oeste 1
        printf("El Semaforo esta en verde para %s\n", verde == 0 ? "Este" : "Oeste");
        usleep(20000);
        //printf(":El semáforo cambio de %s \n", verde == 0 ? "este a oeste" : "oeste a este");
        sem_post(&semaforo);
        timestamp();
    }
}*/

void *activarSemaforo()
{
    for(;;)
    {
        //sem_wait(&semGlobal.cambio_Sentido);
        pthread_mutex_lock(&semGlobal.mutex);
        
        //pthread_cond_wait(&semGlobal.ocupado, &semGlobal.mutex);
        verde = verde == 0 ? 1 : 0;
        printf("El Semaforo esta en verde para %s\n", verde == 0 ? "Este" : "Oeste");
        pthread_cond_broadcast(&semGlobal.ocupado);
        //pthread_cond_broadcast(&puente.semaforo_disponible);
        pthread_cond_broadcast(&puente.semaforo_disponible);
        pthread_cond_broadcast(&puente.vacio);
        pthread_mutex_unlock(&semGlobal.mutex);

        sleep(10);
        //sem_post(&semGlobal.cambio_Sentido);
        if(salidos>= maximo_salidos) 
        {
            printf("FIN DEL PROGRAMA SALIERON %d y el maximo son %d\n", salidos, maximo_salidos);
            return NULL;
        }
    }
}

/*
 *
 */
void entrar (Vehiculo *carro) {
    pthread_mutex_lock(&puente.lock);
    
    // Si el puente esta vacio, puede cambiar la direccion y se suma un carro
    if (puente.contador == 0) {
        printf("Puente en 0\n");
        if((verde == 0 && carro->sentido == ESTE_OESTE) || (verde == 1 && carro->sentido == OESTE_ESTE))
        {
    		carros = 0;
            puente.sentido = carro->sentido;
            puente.contador++;
            salidos++;
            timestamp();
            unsigned int tiempo_cruzando;
            tiempo_cruzando = (puente.largo / max((int) carro->velocidad, 1) * 10) / 1000; 
            printf("(Puente Vacio)Vehículo %c-%d-%d ingresa al puente con el semaforo en %s, durara %d\n", carro->sentido, carro->id, carro->prioridad_creado, 
                verde == 0 ? "Este" : "Oeste", tiempo_cruzando);
            pthread_cond_broadcast(&puente.semaforo_disponible);
            pthread_cond_broadcast(&puente.vacio);
        }
        else
        {
            printf("verde = %d y sentido de carro = %c \n", verde, carro->sentido);
            printf("Puente esta en 0 pero el Vehículo %c-%d-%d pasa a esperar\n", carro->sentido, carro->id, carro->prioridad_creado);
            pthread_cond_wait(&puente.semaforo_disponible, &puente.lock);
        }
    }
    else {
	switch(modalidad){
			case 0:
				// Si hay carros en el puente, pero viajan en la misma direccion puede ingresar
                printf("%s\n","Modo autoregulado");
				if (puente.sentido == carro->sentido) {
					puente.contador++;
					timestamp();
				    printf(": Vehículo %c-%d-%d ingresa al puente\n", carro->sentido, carro->id, carro->prioridad);
				} else {
					timestamp();
					printf(": Vehículo %c-%d-%d pasa a esperar por el puente\n", carro->sentido, carro->id, carro->prioridad);
					// Si hay vehiculos viajando por el puente en la dirección contraria, espera a que se libere
					pthread_cond_wait(&puente.vacio, &puente.lock);
				}
				break;
			case 1: 
				// Si hay carros en el puente, pero viajan en la misma direccion puede ingresar
				if (puente.sentido == carro->sentido) {
					if((verde == 0 && carro->sentido == ESTE_OESTE) || (verde == 1 && carro->sentido == OESTE_ESTE))
        				{  
                           printf("Ojoooo Hay gente en el puente\n");
					       puente.contador++;
                           carro->entro = 1;
					       timestamp();
				           printf(": Vehículo %c-%d ingresa al puente con el semaforo en %s\n", carro->sentido, carro->id, verde == 0 ? "Este" : "Oeste");
        				}
        				else
				        {
				           timestamp();
                           carro->entro = 1;
				           printf("(Modo 1)Vehículo %c-%d pasa a esperar por el puente ya que el semaforo esta ocupado en %s\n", carro->sentido, carro->id,
                            verde == 0 ? "Este" : "Oeste");
				           // Si hay vehiculos viajando por el puente en la dirección contraria, espera a que se libere
				           pthread_cond_wait(&puente.vacio, &puente.lock);
				        }
				} else {
					timestamp();
                    carro->entro = 1;
					printf(": Vehículo %c-%d-%d pasa a esperar por el puente\n", carro->sentido, carro->id, carro->prioridad);
					// Si hay vehiculos viajando por el puente en la dirección contraria, espera a que se libere
					pthread_cond_wait(&puente.vacio, &puente.lock);
				}
				break;
			case 2:
				if (puente.sentido == carro->sentido && carros <= puente.k) {
					puente.contador++;
					carros ++;
					timestamp();
					printf(": Vehículo %c-%d-%d ingresa al puente\n", carro->sentido, carro->id, carro->prioridad);
				} else {
					if (carros > puente.k && puente.sentido == carro->sentido){
						timestamp();
						printf(": Oficial: CAMBIO DE SENTIDO DEL PUENTE\n");
						if (puente.sentido == ESTE_OESTE)
							puente.sentido = OESTE_ESTE;
						else
							puente.sentido = ESTE_OESTE;
						pthread_cond_broadcast(&puente.vacio);
					}
					timestamp();
					printf(": Vehículo %c-%d-%d pasa a esperar por el puente\n", carro->sentido, carro->id, carro->prioridad);
					// Si hay vehiculos viajando por el puente en la dirección contraria, espera a que se libere
					pthread_cond_wait(&puente.vacio, &puente.lock);
				}
				break;
		}
    }
    pthread_mutex_unlock(&puente.lock);
}

/*
 *
 */
void cruzar (Vehiculo *carro) {
        unsigned int tiempo_cruzando;
        tiempo_cruzando = puente.largo / max((int) carro->velocidad, 1) * 10; 
        carro->cruzo = 1;
        timestamp();
        printf(": El vehículo %c-%d está cruzando el puente en %d us.\n", carro->sentido, carro->id, tiempo_cruzando);
        usleep(tiempo_cruzando);
}

/*
 *
 */
void salir (Vehiculo *carro) {
    
    pthread_mutex_lock(&semGlobal.mutex);
    if(posicion_cola == carro->prioridad_creado)
    {
        timestamp();
        printf("Esta saliendo el carro %c-%d-%d, la posicion a salir es %d\n", carro->sentido, carro->id, carro->prioridad_creado, posicion_cola);
        pthread_t actual;
        actual = pthread_self();
        pthread_cancel(actual);
        posicion_cola++;
        salidos++;
        puente.contador--;
        //pthread_cond_broadcast(&semGlobal.ocupado, &semGlobal.mutex);
        //pthread_cond_broadcast(&puente.disponible_salida);
    }
    else
    {
        printf("El carro %c-%d-%d no puede salir porque el que debe salir es la posicion %d\n", 
            carro->sentido, carro->id, carro->prioridad_creado, posicion_cola);
        pthread_cond_wait(&puente.disponible_salida, &puente.lock);
    }
    pthread_mutex_unlock(&semGlobal.mutex);

    /*if(posicion_cola == carro->prioridad_creado)
    {
        puente.contador--;
        timestamp();
        printf(": Vehículo %c-%d está saliendo del puente con prioridad global de %d\n", carro->sentido, carro->id, posicion_cola);
        // Si el contador llega a 0, el puente se vacía y se manda un mensaje a los que estaban esperando
        if (puente.contador == 0) {
            timestamp();
            //UNCOMMENT:printf(": El puente se acaba de vaciar, avisando a los carros del sentido contrario... \n");
            pthread_cond_broadcast(&puente.vacio);
        }
        posicion_cola++;

        if(posicion_cola == prioridad_global)
        {
            printf("FIN\n");
        }
        else
        {
            printf("El siguiente a salir es: %d\n", posicion_cola);
            pthread_cond_broadcast(&puente.disponible_salida);
        }
    }
    else
    {
        printf("%c-%d con prioridad %d quiere salir pero pasa a esperar porque %d falta de salir\n", carro->sentido, carro->id, carro->prioridad_creado,
        posicion_cola);
        usleep(carro->velocidad);
        pthread_cond_wait(&puente.disponible_salida, &puente.lock);
    }*/

}

/*
 * crearVehiculo
 * Crea un vehiculo, ya sea automovil o ambulancia (dependiendo de la
prioridad), con un id
 * y el sentido en el que viaja.
 *
 * @param id
 * @return vehiculo
 */
Vehiculo crearVehiculo (unsigned int id) {
    Vehiculo vehiculo;
    vehiculo.id = id;
    vehiculo.prioridad = 1;

    // Mejorar esto, creo que era sólo por medio de un porcentaje
    double u;
    u = (double) rand() / (double) RAND_MAX;
    /*if (u > 0.5)
    {
        vehiculo.prioridad = AMBULANCIA;
        //vehiculo.prioridad_creado = 0;
    }
    else
    {
        vehiculo.prioridad = CARRO;
        vehiculo.prioridad_creado = prioridad_global;
    }*/

    vehiculo.prioridad = CARRO;
    vehiculo.prioridad_creado = prioridad_global;

    u = (double) rand() / (double) RAND_MAX;
    if (u > 0.5)
        vehiculo.sentido = OESTE_ESTE;
    else
        vehiculo.sentido = ESTE_OESTE;
    vehiculo.velocidad = v_promedio * ((double) rand() / (double) RAND_MAX) * 2;

    prioridad_global++;

    //printf("El carro creado es: id: [%i] velocidad: [%f] sentido:[%c] \n", vehiculo.id, vehiculo.velocidad, vehiculo.sentido);
    
    return vehiculo;
}

/*
 * inicializarPuente
 *
 * @return puente
 */
void inicializarPuente () {
    puente.sentido = ESTE_OESTE; // despues se cambia con el primer carro que entre
    
    if (pthread_mutex_init(&puente.lock, NULL) != 0) {
        printf("\n mutex init failed\n");
    }
    pthread_cond_init(&puente.vacio, NULL);
    puente.contador = 0;
    puente.permiso_entrada = TRUE;
}

void usage(char* program_name){
    printf("Usage: %s modo\n\tEl modo puede ser:\n\t\t0: Auto regulado \
        \n\t\t1: Con semáforo\n\t\t2: Con oficiales de tránsito\n \
        Como segundo parámetro se puede ingresar el número de threads a correr.\
        \nPor defecto es 10.\n", program_name);
    exit(0);
}

void *pasarPuente(Vehiculo *carro)
{
    for(;;)
    {
        pthread_mutex_lock(&semGlobal.mutex);
        pthread_cond_wait(&semGlobal.ocupado, &semGlobal.mutex);
        //printf("Hola Imprimo un carro %d, %c-%d-%d\n", salidos, carro->sentido, carro->id, carro->prioridad_creado);
        
        entrar(carro);
        unsigned int tiempo_cruzando;
        tiempo_cruzando = (puente.largo / max((int) carro->velocidad, 1) * 10) / 1000; 
        //printf("Cruzando %d\n", tiempo_cruzando);
        //salidos++;
        //puente.contador--;
        pthread_cond_broadcast(&semGlobal.ocupado);
        pthread_mutex_unlock(&semGlobal.mutex);
        sleep(tiempo_cruzando);
        salir(carro);
        /*
        cruzar(carro);
        salir(carro);*/
        if(salidos>= maximo_salidos) 
        {
            return NULL;
        }
    }
}

/*
 *
 */
int main(int argc, char **argv) {
    // Inicio - se pide el modo de ejecucion
    unsigned int NUM_THREADS;
    if (argc > 1) {
        modalidad = atoi(argv[1]);
        if (argc > 2) {
			NUM_THREADS = atoi(argv[2]);
			//if (NUM_THREADS < 0)
				//NUM_THREADS = 10;
		}
		else
			NUM_THREADS = 10;
        if (modalidad < 0 && modalidad > 2)
            usage(argv[0]);
    } else 
        usage(argv[0]);
    int parametros_asignados = asignarParametros();
    if(parametros_asignados != 0) {
        printf("\nLos parametros no fueron asignados\n");
        return EXIT_FAILURE;
    }

    // Setea la semilla para el random
    srand(time(NULL));
    
    int err;
    
    pthread_t tabla_threads[NUM_THREADS];
	Vehiculo vehiculos[NUM_THREADS];

    // inicializar puente
    inicializarPuente();

    double x, u;
    int i;
    int fallo;
    verde = 1;
    prioridad_global = 1;
    salidos = 0;
    maximo_salidos = NUM_THREADS;
    pthread_t init_sem;
    pthread_t hilocarro;
    pthread_t hilocarro2;

    //Semaphore mode
    if(modalidad == 1)
    {   
        pthread_create(&init_sem, NULL, activarSemaforo, NULL);
    }

    printf("Se crearan %d hilos\n", NUM_THREADS);
    
    for (i=0; i < NUM_THREADS; i++) {
        // generador de tiempos para media de vehiculos x = numero random con distribucion exponencial  u = numero random con distribucion uniforme
        u = (double) rand() / (double) RAND_MAX;
        x = - log(u) / (1.00 / media_vehiculos) * 100;
        // Esperamos para que el vehiculo se integre
        //usleep((int) x);

        // Se crea el thread del vehiculo para solicitar pasar el puente
        vehiculos[i] = crearVehiculo(i);

        unsigned int tiempo_cruzando;
        tiempo_cruzando = (puente.largo / max((int) vehiculos[i].velocidad, 1) * 10) / 1000; 
        sleep(tiempo_cruzando);

        pthread_create(&tabla_threads[i], NULL, (void*)&pasarPuente, (void*)&vehiculos[i]);
        if (err) {
            return EXIT_FAILURE;
        }
    }

    pthread_join(init_sem, NULL);

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(tabla_threads[i], NULL);
        //pthread_detach(tabla_threads[i]);
    }

    // Se libera el lock
    pthread_mutex_destroy(&puente.lock);

    return EXIT_SUCCESS;
}
