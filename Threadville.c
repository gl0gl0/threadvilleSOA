#include "Threadville.h"

void etiquetar(char* etiqueta, int i){
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
			sprintf(etiqueta, "%c0%d", 65+letra, num);
		else
			sprintf(etiqueta, "%c%d", 65+letra, num);
	} else{
		if (i>=480 && i<644){
			i -= 480;
			letra = (i / 41);
			num = i % 41;
			if (num < 10)
				sprintf(etiqueta, "%c0%d", 48+letra, num);
				else
				sprintf(etiqueta, "%c%d", 48+letra, num);
		}
		if (i>=644 && i<674){
			i -= 644;
			letra = (i / 6);
			num = i % 6;
			switch(letra){
				case 0:
					sprintf(etiqueta, "LA%d", num);
					break;
				case 1:
					sprintf(etiqueta, "CU%d", num);
					break;
				case 2:
					sprintf(etiqueta, "MO%d", num);
					break;
				case 3:
					sprintf(etiqueta, "SH%d", num);
					break;
				case 4:
					sprintf(etiqueta, "JO%d", num);
					break;
			}
		}
		if (i>=674 && i<714){
			i -= 674;
			letra = (i / 20);
			num = i % 20;
			if (num < 10)
				sprintf(etiqueta, "%c0%d", 89+letra, num);
				else
				sprintf(etiqueta, "%c%d", 89+letra, num);
		}
	}
}

/*int main(int argc, char* argv){
	return 0;
}*/
