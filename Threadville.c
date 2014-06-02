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
	if (pos >=7 && pos <=14 || pos >=35 && pos <=42 || pos >=63 && pos <=70 || pos >=91 && pos <=98 ||
		pos >=119 && pos <=126 || pos >=147 && pos <=154) {
		ret.x = pos / 28 * 140 + 20 * (pos % 28 -7 + pos / 28);
		ret.y = 0;
	}
	if (pos >=21 && pos <=27 || pos >=49 && pos <=55 || pos >=77 && pos <=83 || pos >=105 && pos <=111 ||
		pos >=133 && pos <=139 || pos >=161 && pos <=167) {
		pos = (-(pos - (pos / 28 + 1) * 28)) + 7 + pos / 28 * 28;
		ret.x = pos / 28 * 140 + 20 * (pos % 28 -7 + pos / 28);
		ret.y = 140;
	}
	if (pos == 0 || pos == 28 || pos == 56 || pos == 84 || pos == 112 || pos == 140){
		ret.x = 160 * (pos / 28);
		ret.y = 140;
	}
	if (pos >=319 && pos <=326 || pos >=347 && pos <=354 || pos >=375 && pos <=382 || pos >=403 && pos <=410 ||
		pos >=431 && pos <=438 || pos >=459 && pos <=466) {
		pos -= 312;
		ret.x = pos / 28 * 140 + 20 * (pos % 28 -7 + pos / 28);
		ret.y = 520;
	}
	if (pos >=333 && pos <=339 || pos >=361 && pos <=367 || pos >=389 && pos <=395 || pos >=417 && pos <=423 ||
		pos >=445 && pos <=451 || pos >=473 && pos <=479) {
		pos -= 312;
		pos = (-(pos - (pos / 28 + 1) * 28)) + 7 + pos / 28 * 28;
		ret.x = pos / 28 * 140 + 20 * (pos % 28 -7 + pos / 28);
		ret.y = 660;
	}
	if (pos == 312 || pos == 340 || pos == 368 || pos == 396 || pos == 424 || pos == 452){
		ret.x = 28 * (pos-312) / 28;
		ret.y = 660;
	}
	if (pos >=1 && pos <=6 || pos >=29 && pos <=34 || pos >=57 && pos <=62 || pos >=85 && pos <=90 ||
		pos >=113 && pos <=118 || pos >=141 && pos <=146) {
		ret.x = 160 * (pos / 28);
		pos = 7 - (pos - pos / 28 * 28) + pos / 28 * 28;
		ret.y = (pos - pos / 28 * 28) * 20;
	}
	ret.x += borderwidth;
	return ret;
}
