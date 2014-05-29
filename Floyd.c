#include "Threadville.h"

int Threadville[N][N];
int Sucesores[N][N];

automovil* autos[4];

void llenarMatriz(){
	int i, j;
	for (i=0; i<N; i++){
		for (j=0; j<N; j++){
			Threadville[i][j] = 9999999;
			Sucesores[i][j] = -1;
		}
	}
	for (i=0; i<N; i++){
		Threadville[i][i] = 0;
		if (i == 27 || i == 55 || i == 83 || i == 111 || i == 139 || i == 167 ||
			i == 339 || i == 367 || i == 395 || i == 423 || i == 451 || i == 479){
			Threadville[i][i-27] = 1; Sucesores[i][i-27] = i-27;
		}
		else if (i == 173 || i == 185 || i == 197 || i == 209 || i == 221 || i == 233 ||
				i == 179 || i == 191 || i == 203 || i == 215 || i == 227 || i == 239 ||
				i == 257 || i == 269 || i == 281 || i == 293 || i == 305 || i == 245 ||
				i == 251 || i == 263 || i == 275 || i == 287 || i == 299 || i == 311 ||
				i == 520 || i == 561 || i == 602 || i == 643 || i == 649 || i == 655 ||
				i == 661 || i == 667 || i == 673 || i == 693 || i == 713){
					Threadville[173][0] = 1; Sucesores[173][0] = 0;
					Threadville[185][28] = 1; Sucesores[185][28] = 28;
					Threadville[197][56] = 1; Sucesores[197][56] = 56;
					Threadville[209][84] = 1; Sucesores[209][84] = 84;
					Threadville[221][112] = 1; Sucesores[221][112] = 112;
					Threadville[233][140] = 1; Sucesores[233][140] = 140;
					Threadville[179][644] = 1;  Sucesores[179][644] = 644;
					Threadville[191][650] = 1; Sucesores[191][650] = 650;
					Threadville[203][656] = 1; Sucesores[203][656] = 656;
					Threadville[215][662] = 1; Sucesores[215][662] = 662;
					Threadville[227][668] = 1; Sucesores[227][668] = 668;
					Threadville[239][696] = 1; Sucesores[239][696] = 696;
					Threadville[257][649] = 1; Sucesores[257][649] = 649;
					Threadville[269][655] = 1; Sucesores[269][655] = 655;
					Threadville[281][661] = 1; Sucesores[281][661] = 661;
					Threadville[293][667] = 1; Sucesores[293][667] = 667;
					Threadville[305][673] = 1; Sucesores[305][673] = 673;
					Threadville[245][676] = 1; Sucesores[245][676] = 676;
					Threadville[251][326] = 1; Sucesores[251][326] = 326;
					Threadville[263][354] = 1; Sucesores[263][354] = 354;
					Threadville[275][382] = 1; Sucesores[275][382] = 382;
					Threadville[287][410] = 1; Sucesores[287][410] = 410;
					Threadville[299][438] = 1; Sucesores[299][438] = 438;
					Threadville[311][466] = 1; Sucesores[311][466] = 466;
					Threadville[520][701] = 1; Sucesores[520][701] = 701;
					Threadville[561][700] = 1; Sucesores[561][700] = 700;
					Threadville[602][679] = 1; Sucesores[602][679] = 679;
					Threadville[643][680] = 1; Sucesores[643][680] = 680;
					Threadville[693][674] = 1; Sucesores[693][674] = 674;
					Threadville[713][694] = 1; Sucesores[713][694] = 694;
					Threadville[649][246] = 1; Sucesores[649][246] = 246;
					Threadville[655][258] = 1; Sucesores[655][258] = 258;
					Threadville[661][270] = 1; Sucesores[661][270] = 270;
					Threadville[667][282] = 1; Sucesores[667][282] = 282;
					Threadville[673][294] = 1; Sucesores[673][294] = 294;
			}
			else{
				if (i == 14 || i == 42 || i == 70 || i == 98 || i == 126 ||
					i == 326 || i == 354 || i == 382 || i == 410 || i == 438){
					Threadville[i][i+21] = 1; Sucesores[i][i+21] = i+21;
				}
				if (i == 28 || i == 56 || i == 84 || i == 112 || i == 140 ||
					i == 340 || i == 368 || i == 396 || i == 424 || i == 452){
					Threadville[i][i-7] = 1; Sucesores[i][i-7] = i-7;
				}
				if (i == 21 || i == 49 || i == 77 || i == 105 || i == 133 || i == 161 ||
					i == 319 || i == 347 || i == 375 || i == 403 || i == 431 || i == 459 ||
					i == 678 || i == 698 || i == 681 || i == 702){
						Threadville[21][174] = 1; Sucesores[21][174] = 174;
						Threadville[49][186] = 1; Sucesores[49][186] = 186;
						Threadville[77][198] = 1; Sucesores[77][198] = 198;
						Threadville[105][210] = 1; Sucesores[105][210] = 210;
						Threadville[133][222] = 1; Sucesores[133][222] = 222;
						Threadville[161][234] = 1; Sucesores[161][234] = 234;
						Threadville[319][240] = 1; Sucesores[319][240] = 240;
						Threadville[347][252] = 1; Sucesores[347][252] = 252;
						Threadville[375][264] = 1; Sucesores[375][264] = 264;
						Threadville[403][276] = 1; Sucesores[403][276] = 276;
						Threadville[431][288] = 1; Sucesores[431][288] = 288;
						Threadville[459][300] = 1; Sucesores[459][300] = 300;
						Threadville[681][168] = 1; Sucesores[681][168] = 168;
						Threadville[702][306] = 1; Sucesores[702][306] = 306;
						Threadville[678][480] = 1; Sucesores[678][480] = 480;
						Threadville[698][562] = 1; Sucesores[698][562] = 562;
						Threadville[678][521] = 1; Sucesores[678][521] = 521;
						Threadville[698][603] = 1; Sucesores[698][603] = 603;
					}
				Threadville[644][180] = 1; Sucesores[644][180] = 180;
				Threadville[650][192] = 1; Sucesores[650][192] = 192;
				Threadville[656][204] = 1; Sucesores[656][204] = 204;
				Threadville[662][216] = 1; Sucesores[662][216] = 216;
				Threadville[668][228] = 1; Sucesores[668][228] = 228;
				Threadville[i][i+1] = 1; Sucesores[i][i+1] = i+1;
			}
			if ((i >= 645 && i <= 649) || (i >= 651 && i <= 655) ||
				(i >= 657 && i <= 661) || (i >= 663 && i <= 667) ||
				(i >= 669 && i <= 673) ){
					Threadville[i][i-1] = 1; Sucesores[i][i-1] = i-1;
				}
				
	}
}

void Floyd(){
	int i, j, k;
	for (k=0; k<N; k++){
		for (i=0; i<N; i++){
			for (j=0; j<N; j++){
				if (Threadville[i][k] + Threadville[k][j] < Threadville[i][j]){
					Threadville[i][j] = Threadville[i][k] + Threadville[k][j];
					Sucesores[i][j] = Sucesores[i][k];
				}
			}
		}
	}
}

void escribirArchivo(){
	FILE *f = fopen("file.txt", "w");
	if (f == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	int i , j;
	for (i=0; i<N; i++){
		for (j=0; j<N; j++){
			if (Threadville[i][j] == 9999999)
				fprintf(f, "_\t");
			else
				fprintf(f, "%d\t", Threadville[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

int anterior;
int sentido_puente;

void avanzar(automovil* a){
	if (anterior == 185 || anterior == 197 || anterior == 209 || anterior == 221 || anterior == 233)
		if (Sucesores[Sucesores[a->posicion][a->destino[1]]][a->destino[1]]+11 == anterior){
			a->posicion++;
			return;
		}
	if (anterior == 251 || anterior == 263 || anterior == 275 || anterior == 287 || anterior == 299)
		if (Sucesores[Sucesores[a->posicion][a->destino[1]]][a->destino[1]]-1 == anterior){
			a->posicion++;
			return;
		}
	if (anterior == 179 || anterior == 191 || anterior == 203 || anterior == 215 || anterior == 227)
		if (a->posicion == 644 || a->posicion == 650 || a->posicion == 656 || a->posicion == 662 || a->posicion == 668){
			sentido_puente = 1;
			a->posicion++;
			return;
		}
	if (anterior == 257 || anterior == 269 || anterior == 281 || anterior == 293 || anterior == 305)
		if (a->posicion == 649 || a->posicion == 655 || a->posicion == 661 || a->posicion == 667 || a->posicion == 673){
			sentido_puente = -1;
			a->posicion--;
			return;
		}
	if (sentido_puente == 1){
		switch(a->posicion){
			case 649: a->posicion = 246; return;
			case 655: a->posicion = 258; return;
			case 661: a->posicion = 270; return;
			case 667: a->posicion = 282; return;
			case 673: a->posicion = 294; return;
		}
	}
	
	if (sentido_puente == -1){
		switch(a->posicion){
			case 644: a->posicion = 180; return;
			case 650: a->posicion = 192; return;
			case 656: a->posicion = 204; return;
			case 662: a->posicion = 216; return;
			case 668: a->posicion = 228; return;
		}
	}
	if ((a->posicion >= 645 && a->posicion <= 648) || (a->posicion >= 651 && a->posicion <= 654) ||
	(a->posicion >= 657 && a->posicion <= 660) || (a->posicion >= 663 && a->posicion <= 666) ||
	(a->posicion >= 669 && a->posicion <= 672) ){
		a->posicion += sentido_puente;
		return;
	}
	anterior = a->posicion;
	a->posicion = Sucesores[a->posicion][a->destino[1]];
}



void loop(void* carro){
	char e[3];
	automovil* a;
	a = (automovil*) carro;
	etiquetar(e, a->posicion);
	printf("%d_%s\t", a->destino[0], e);
	while (a->posicion != a->destino[1]){
		avanzar(a);
		etiquetar(e, a->posicion);
		printf("%d_%s\t", a->destino[0], e);
	}
}

void generarCarro(automovil* a){
	int r;
	r = rand() % 714;
	a->posicion = a->destino[0] = 109;
	r = rand() % 714;
	a->destino[1] = 539;
	char e[3], f[3];
	etiquetar(e, a->destino[0]);
	etiquetar(f, a->destino[1]);
	printf("!!!%d(%s)- %d(%s)\n", a->destino[0],  e, a->destino[1], f);
	pthread_create(&a->hilo, NULL, loop, (void *) a);
	pthread_join(a->hilo, NULL);
}

int main(int argc, char* argv){
	printf("inicio llenarMatriz\n");
	llenarMatriz();
	printf("fin llenarMatriz\n");
	printf("inicio Floyd\n");
	Floyd();
	printf("fin Floyd\n");
	sentido_puente = 1;
	int i;
	srand(time(NULL));
	for (i=0; i<1; i++){
		autos[i] = (automovil *) malloc(sizeof(automovil));
		generarCarro(autos[i]);
	}

	printf("\n");
	return 0;
}
