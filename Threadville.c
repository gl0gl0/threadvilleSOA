#include "Threadville.h"

int sentido_puente[5];

void etiquetar(int i){
	int letra, num;
	if (i<480){
		if (i>=0 && i<168){
			letra = i / 28;
			num = i % 28;
		}
		if (i>=168 && i<312){
			i -= 168;
			letra = (i / 12) +6;
			num = i % 12;
		}
		if (i>=312 && i<480){
			i -= 312;
			letra = (i / 28) + 18;
			num = i % 28;
		}
		if (num < 10)
			printf("%c0%d ", 65+letra, num);
		else
			printf("%c%d ", 65+letra, num);
	} else{
		if (i>=480 && i<644){
			i -= 480;
			letra = (i / 41);
			num = i % 41;
			if (num < 10)
				printf("%c0%d ", 48+letra, num);
			else
				printf("%c%d ", 48+letra, num);
		}
		if (i>=644 && i<674){
			i -= 644;
			letra = (i / 6);
			num = i % 6;
			switch(letra){
				case 0:
					printf("LA%d ", num);
					break;
				case 1:
					printf("CU%d ", num);
					break;
				case 2:
					printf("MO%d ", num);
					break;
				case 3:
					printf("SH%d ", num);
					break;
				case 4:
					printf("JO%d ", num);
					break;
			}
		}
		if (i>=674 && i<714){
			i -= 674;
			letra = (i / 20);
			num = i % 20;
			if (num < 10)
				printf("%c0%d ", 89+letra, num);
			else
				printf("%c%d ", 89+letra, num);
		}
	}
}

int avanzar(automovil* a){
	//printf("?%d?%d?", sentido_puente[4], a->anterior);
	if (a->anterior == 185 || a->anterior == 197 || a->anterior == 209 || a->anterior == 221 || a->anterior == 233)
		if (Sucesores[Sucesores[a->posicion][a->destino[1]]][a->destino[1]]+11 == a->anterior)
			return a->posicion + 1;
	if (a->anterior == 251 || a->anterior == 263 || a->anterior == 275 || a->anterior == 287 || a->anterior == 299)
		if (Sucesores[Sucesores[a->posicion][a->destino[1]]][a->destino[1]]-1 == a->anterior)
			return a->posicion + 1;
	if (a->anterior == 179 || a->anterior == 191 || a->anterior == 203 || a->anterior == 215 || a->anterior == 227){
		switch(a->posicion){
			case 644: sentido_puente[0] = 1; return a->posicion + 1;
			case 650: sentido_puente[1] = 1; return a->posicion + 1;
			case 656: sentido_puente[2] = 1; return a->posicion + 1;
			case 662: sentido_puente[3] = 1; return a->posicion + 1;
			case 668: sentido_puente[4] = 1; return a->posicion + 1;			
		}
	}
	if (a->anterior == 257 || a->anterior == 269 || a->anterior == 281 || a->anterior == 293 || a->anterior == 305){
		switch(a->posicion){
			case 649: sentido_puente[0] = -1; return a->posicion - 1;
			case 655: sentido_puente[1] = -1; return a->posicion - 1;
			case 661: sentido_puente[2] = -1; return a->posicion - 1;
			case 667: sentido_puente[3] = -1; return a->posicion - 1;
			case 673: sentido_puente[4] = -1; return a->posicion - 1;			
		}
	}
	switch(a->posicion){
		case 649: if (sentido_puente[0] == 1) return 246;
		case 655: if (sentido_puente[1] == 1) return 258;
		case 661: if (sentido_puente[2] == 1) return 270;
		case 667: if (sentido_puente[3] == 1) return 282;
		case 673: if (sentido_puente[4] == 1) return 294;
		case 644: if (sentido_puente[0] == -1) return 180;
		case 650: if (sentido_puente[1] == -1) return 192;
		case 656: if (sentido_puente[2] == -1) return 204;
		case 662: if (sentido_puente[3] == -1) return 216;
		case 668: if (sentido_puente[4] == -1) return 228;
	}
	if ((a->posicion >= 645 && a->posicion <= 648) || (a->posicion >= 651 && a->posicion <= 654) ||
	(a->posicion >= 657 && a->posicion <= 660) || (a->posicion >= 663 && a->posicion <= 666) ||
	(a->posicion >= 669 && a->posicion <= 672) ){
		return a->posicion + sentido_puente[(a->posicion-645) / 6];
	}
	a->anterior = a->posicion;
	return Sucesores[a->posicion][a->destino[1]];
}

void init(){
	llenarMatriz();
	Floyd();
}

point toCanvas(int pos){
	point ret;
	if (pos >=7 && pos <=14){
		ret.x = ((pos / 28 * 7 + pos % 28) - 7) * 20;
		ret.y = 0;
	}
	if (pos >=35 && pos <=42 || pos >=63 && pos <=70 || pos >=91 && pos <=98 ||
		pos >=119 && pos <=126 || pos >=147 && pos <=154) {
		ret.x = ((pos / 28 * 7 + pos % 28) - 6) * 20;
		ret.y = 0;
	}
	ret.x += borderwidth;
	return ret;
}
