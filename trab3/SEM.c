//Criptografia - Yeda Venturini - 2016/1
//Gustavo Almeida Rodrigues - 489999
//Algoritmo de Exponenciação Modular
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long int expAlgorithm(long long int base, long long int exponent, long long int modulus){
	long long int resultado = 1;

	assert((modulus - 1) * (modulus - 1));
	base = base % modulus;

	while(exponent > 0){
		if(exponent % 2 == 1){
			resultado = (resultado * base) % modulus;
		}
		exponent = exponent >> 1;
		base = (base * base) % modulus;
	}

	return resultado;
}

int main(){
	long long int base = 0;
	long long int exponent = 0;
	long long int modulus = 0;

	scanf("%llu %llu %llu", &base, &exponent, &modulus);

	printf("%llu\n", expAlgorithm(base, exponent, modulus));

	return 0;
}