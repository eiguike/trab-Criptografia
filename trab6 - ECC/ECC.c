#include <stdio.h>
#include <stdlib.h>

int main(){
	int G[2] = {0,0};
	int Q[2] = {0,0};
	int R[2] = {0,0};
	int IG[2] = {0,0};
	int IQ[2] = {0,0};
	int n = 0, a = 0, p = 0;
	int fi = 0;
	int aux = 0;

	do{
		scanf("%d", &n);
		if(n != 0){
			scanf("%d %d %d %d", &a, &p, &G[0], &G[1]);

			// Aqui faz a primeira soma
			Q[0] = G[0];
			Q[1] = G[1];
			R[0] = G[0];
			R[1] = G[1];

			for(aux = 1; aux < n; aux++){
				// Aqui a gente gera a inversa da G seguindo o que estava no AVA
				IG[0] = G[0];
				if(((p - G[1]) % p) < 0)
					IG[1] = ((p - G[1]) % p) + p;
				else
					IG[1] = (p - G[1]) % p;

				// Aqui a gente gera a inversa da Q seguindo o que estava no AVA
				IQ[0] = Q[0];
				if(((p - Q[1]) % p) < 0)
					IQ[1] = ((p - Q[1]) % p) + p;
				else
					IQ[1] = (p - Q[1]) % p;

				// Aqui verifica se o G não é vazio (pois caso seja vazio, a soma irá ser o próprio valor definido no Q)
				if(G[0] != 0 && G[1] != 0){
					// Caso os valores de G não sejam vazio (0) então irá passar o valor de G pra Q
					if(Q[0] == 0 && Q[1] == 0){
						Q[0] = G[0];
						Q[1] = G[1];
					// Aqui verifica caso seja igual a inversa
					}else if((G[0] == IQ[0] && G[1] == IQ[1]) || (Q[0] == IG[0] && Q[1] == IG[1])){
						Q[0] = 0;
						Q[1] = 1;
					// Aqui verifica se são diferentes
					}else if(G[0] != Q[0] && G[1] != Q[1]){
						// Faz o cálculo do FI
						if(((G[1] - Q[1]) / (G[0] - G[0])) % p < 0)
							// Aqui na real precisa ser feito a divisão corretamente
							fi = (((G[1] - Q[1]) / (G[0] - G[0])) % p) + p;
						else
							// Aqui na real precisa ser feito a divisão corretamente
							fi = ((G[1] - Q[1]) / (G[0] - G[0])) % p;
					// Caso sejam iguais
					}else{
						// Faz o cálculo do FI
						if(((3 * (Q[0]^2) + a) / (2 * Q[1])) % p < 0)
							// Aqui na real precisa ser feito a divisão corretamente
							fi = (((3 * (Q[0]^2) + a) / (2 * Q[1])) % p) + p;
						else
							// Aqui na real precisa ser feito a divisão corretamente
							fi = ((3 * (Q[0]^2) + a) / (2 * Q[1])) % p;
					}
					
					R[0] = ;
					R[1] = ;
				}
			}
		}
	}while(n != 0);
}