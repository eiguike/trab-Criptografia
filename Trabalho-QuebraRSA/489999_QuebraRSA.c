#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void decrypt(int N, int E, int C);
int* semiprime(int valor);
int euclidesEstendido(int a, int b);

int main(){
	int N, E, C;

	scanf("%d %d %d", &N, &E, &C);

	// Faz a verificação da entrada
	if( (N >= 15 && N <= 1000000000) && (E >= 1 && E < N) && (C >= 1 && C < N) ){
		// Se tudo está ok passa para a função
		decrypt(N, E, C);
	}

	return 0;
}

// Função SEM que recebe os valores para cálculo do resultado M
long long int expAlgorithm(long long int base, long long int exponent, long long int modulus){
	long long int resultado = 1;

	// Verifica se é válida a multiplicação
	assert((modulus - 1) * (modulus - 1));
	base = base % modulus; // Encontra o módulo da base

	// Nesse while vai abrindo o expoente
	while(exponent > 0){
		if(exponent % 2 == 1){
			resultado = (resultado * base) % modulus;
		}
		exponent = exponent >> 1;
		base = (base * base) % modulus;
	}

	return resultado;
}

// Função EEA que recebe dois valores e devolve a inversa
int euclidesEstendido(int a, int b){
	int x[2] = {1, 0};
	int y[2] = {0, 1};
	int quociente = 0;
	int aux = 0;
	int auxX = 0, auxY = 0;
	int store = b;

	// Encontra o GDC e a inversa
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
		if(x[1] < 0){ // Caso a inversa seja um valor negativo, adiciona o valor inicial para encontrar o positivo
			return x[1] + store;
		}else{
			return x[1];
		}
	}else{
		return 0;
	}
}

// Função que decompõe o semiprimo em 2 valores P e Q primos
int* semiprime(int valor){
    int *factors = malloc(sizeof(int) * 0);
    int i = 0;
    int tamanho = 0;

    // Faz a divisão quando encontrar os primos e salva ambos encontrados no factors
    for (i = 2; i <= valor / i; i++) {
      while (valor % i == 0) {
      	tamanho++;
        factors = realloc(factors, sizeof(int) * tamanho);
        factors[tamanho-1] = i;
        valor /= i;
      }
    }

    if (valor > 1) {
      tamanho++;
      factors = realloc(factors, sizeof(int) * tamanho);
      factors[tamanho-1] = valor;
    }

    return factors;
}

void decrypt(int N, int E, int C){
	int *valores = NULL;
	int P = 0, Q = 0, D = 0;
	int totN = 0;
	long long int aux = 0;
	int resultado;

	// Aqui no caso preciso descobrir os valores de P e Q
	// Função que decompõe o N (semi primo) em dois primos P e Q
	valores = semiprime(N); 

	// Deixa definido os valores de P e Q que serão usados na função totiente
	P = valores[0];
	Q = valores[1];

	// Aqui no caso eu necessito descobrir a função totiente
	// Faz a função totiente de N
	totN = (P - 1) * (Q - 1);

	// Nesse caso, já possuímos o valor de E, que é a chave pública. Agora precisamos encontrar o valor de D utilizando
	// o EEA (Euclidean Extended Algorithm)
	D = euclidesEstendido(E, totN);
	
	// Depois é necessário decriptografar a mensagem utilizando N e D:
	// M = C^D (mod N)

	aux = expAlgorithm(C, D, N);
	resultado = aux;

	printf("%d\n", resultado);
}