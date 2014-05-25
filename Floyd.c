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
			Threadville[i][j] = 0;
		}
	}
	int s14;
	s14 = 0;
	for (i=0; i<N; i++){
		for (j=0; j<N; j++){
			if (s14 == 14){
				s14 = 0;
				Threadville[i][j] = j + 
			}
			Threadville[i][j] = j + 1;
		}
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

int main(int argc, char* argv){
	Floyd();
	return 0;
}
