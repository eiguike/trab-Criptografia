//Criptografia - Yeda Venturini - 2016/1
//Gustavo Almeida Rodrigues - 489999
//Algoritmo de Euclides Estendido
#include <stdio.h>
#include <stdlib.h>

void euclidesEstendido(int a, int b){
	int x[2] = {1, 0};
	int y[2] = {0, 1};
	int quociente = 0;
	int aux = 0;
	int auxX = 0, auxY = 0;
	int store = b;

	while(a % b != 0){
		quociente = a / b;

		aux = a;
		a = b;
		b = aux % b;

		auxX = x[0] - (x[1] * quociente);
		auxY = y[0] - (y[1] * quociente);

		x[0] = x[1];
		x[1] = auxX;
		y[0] = y[1];
		y[1] = auxY;
	}

	if(b == 1){
		if(x[1] < 0){
			printf("X: %d %d\nY: %d %d\na: %d\nb: %d\n", x[0], x[1] + store, y[0], y[1], a, b);
		}else{
			printf("X: %d %d\nY: %d %d\na: %d\nb: %d\n", x[0], x[1], y[0], y[1], a, b);
		}
	}else{
		printf("%d N\n", b);
	}
}

int main(){
	int a = 0, b = 0;

	scanf("%d %d", &a, &b);
	if(a > b)
		euclidesEstendido(b,a);
	else
		euclidesEstendido(a,b);

	return 0;
}