#include<stdio.h>
#include<stdlib.h>

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#define N 714

int Threadville[N][N];



void llenarMatriz(){
	int i, j;
	for (i=0; i<N; i++){
		for (j=0; j<N; j++){
			Threadville[i][j] = 9999999;
		}
	}
	for (i=0; i<N; i++){
		Threadville[i][i] = 0;
		if (i == 27 || i == 55 || i == 83 || i == 111 || i == 139 || i == 167 ||
			i == 339 || i == 367 || i == 395 || i == 423 || i == 451 || i == 479)
			Threadville[i][i-27] = 1;
		else if (i == 173 || i == 185 || i == 197 || i == 209 || i == 221 || i == 233 ||
				i == 179 || i == 191 || i == 203 || i == 215 || i == 227 || i == 239 ||
				i == 257 || i == 269 || i == 281 || i == 293 || i == 305 || i == 245 ||
				i == 251 || i == 263 || i == 275 || i == 287 || i == 299 || i == 311 ||
				i == 520 || i == 561 || i == 602 || i == 643 || i == 649 || i == 655 ||
				i == 661 || i == 667 || i == 673 || i == 693 || i == 713){
					Threadville[173][0] = 1;
					Threadville[185][28] = 1;
					Threadville[197][56] = 1;
					Threadville[209][84] = 1;
					Threadville[221][112] = 1;
					Threadville[233][140] = 1;
					Threadville[179][644] = 1;
					Threadville[191][650] = 1;
					Threadville[203][656] = 1;
					Threadville[215][662] = 1;
					Threadville[227][668] = 1;
					Threadville[239][694] = 1;
					Threadville[257][649] = 1;
					Threadville[269][655] = 1;
					Threadville[281][661] = 1;
					Threadville[293][667] = 1;
					Threadville[305][673] = 1;
					Threadville[245][674] = 1;
					Threadville[251][326] = 1;
					Threadville[263][354] = 1;
					Threadville[275][382] = 1;
					Threadville[287][410] = 1;
					Threadville[299][438] = 1;
					Threadville[311][466] = 1;
					Threadville[520][701] = 1;
					Threadville[561][701] = 1;
					Threadville[602][681] = 1;
					Threadville[643][681] = 1;
					Threadville[693][674] = 1;
					Threadville[713][694] = 1;
					Threadville[649][246] = 1;
					Threadville[655][258] = 1;
					Threadville[661][270] = 1;
					Threadville[667][282] = 1;
					Threadville[673][294] = 1;
			}
			else{
				if (i == 14 || i == 42 || i == 70 || i == 98 || i == 126 || i == 154 ||
					i == 326 || i == 354 || i == 382 || i == 410 || i == 438 || i == 466)
					Threadville[i][i+21] = 1;
				if (i == 28 || i == 56 || i == 84 || i == 112 || i == 140 ||
					i == 340 || i == 368 || i == 396 || i == 424 || i == 452)
					Threadville[i][i-7] = 1;
				if (i == 21 || i == 49 || i == 77 || i == 105 || i == 133 || i == 161 ||
					i == 319 || i == 347 || i == 375 || i == 403 || i == 431 || i == 459 ||
					i == 678 || i == 698 || i == 684 || i == 704){
						Threadville[21][174] = 1;
						Threadville[49][186] = 1;
						Threadville[77][198] = 1;
						Threadville[105][210] = 1;
						Threadville[133][222] = 1;
						Threadville[161][234] = 1;
						Threadville[319][240] = 1;
						Threadville[347][252] = 1;
						Threadville[375][264] = 1;
						Threadville[403][276] = 1;
						Threadville[431][288] = 1;
						Threadville[459][300] = 1;
						Threadville[684][168] = 1;
						Threadville[704][306] = 1;
						Threadville[678][480] = 1;
						Threadville[698][562] = 1;
						Threadville[678][521] = 1;
						Threadville[698][603] = 1;
					}
				Threadville[644][180] = 1;
				Threadville[650][192] = 1;
				Threadville[656][204] = 1;
				Threadville[662][216] = 1;
				Threadville[668][228] = 1;
				Threadville[i][i+1] = 1;
			}
			if ((i >= 645 && i <= 649) || (i >= 651 && i <= 655) ||
				(i >= 657 && i <= 661) || (i >= 663 && i <= 667) ||
				(i >= 669 && i <= 673) )
					Threadville[i][i-1] = 1;
	}
}

void Floyd(){
	int i, j, k;
	for (k=0; k<N; k++){
		for (i=0; i<N; i++){
			for (j=0; j<N; j++){
				Threadville[i][j] = min(Threadville[i][j], Threadville[i][k] + Threadville[k][j]);
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

int main(int argc, char* argv){
	llenarMatriz();
	Floyd();
	escribirArchivo();
	return 0;
}
