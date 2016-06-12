#include <stdio.h>
#include <stdlib.h>

int extendedEuclidean(int valor, int p, int *coefA, int *coefB){
	int coefAux = 0;
	int coefBux = 0;
	int aux;

	//aqui no caso é o último caso da recursão
	if(p == 0){
		*coefA = 1;
		*coefB = 0;

		return valor;
	}

	aux = extendedEuclidean(p, valor % p, &coefAux, &coefBux);
	*coefA = coefBux;
	*coefB = coefAux - (valor/p) * coefBux;

	return aux;
}

int inversaModular(int valor, int p){
	int inversa;
	int coefA, coefB;

	inversa = extendedEuclidean(valor, p, &coefA, &coefB);

	if(coefA < 0)
		coefA += p;

	inversa = coefA;

	return inversa;
}

void calculaResultado(int Xg, int Yg, int *Xq, int *Yq, int fi, int p){
	int aux = *Xq;

	*Xq = ((fi * fi) - (aux) - Xg);
	*Xq = (*Xq) % p;

	if((*Xq) < 0)
		(*Xq) += p;

	*Yq = (fi * ((aux) - (*Xq)) - (*Yq));
	*Yq = (*Yq) % p;

	if((*Yq) < 0)
		(*Yq) += p;
}

void somaPontos(int Xg, int Yg, int *Xq, int *Yq, int p){
	int fi;
	int PP;
	int SP;

	PP = (Yg - *Yq) % p;
	if(PP < 0)
		PP += p;

	SP = (Xg - *Xq) % p;
	if(SP < 0)
		SP += p;
	SP = inversaModular(SP, p);

	fi = PP * SP;
	fi = fi % p;
	if(fi < 0)
		fi += p;

	calculaResultado(Xg, Yg, Xq, Yq, fi, p);
}

void multiplicaPontos(int Xg, int Yg, int *Xq, int *Yq, int p, int a){
	int fi;
	int PP;
	int SP;

	PP = (3 * ((*Xq) * (*Xq))) + a;
	PP = PP % p;
	if(PP < 0)
		PP += p;

	SP = 2 * (*Yq);
	SP = SP % p;
	if(SP < 0)
		SP += p;
	SP = inversaModular(SP, p);

	fi = PP * SP;
	fi = fi % p;
	if(fi < 0)
		fi += p;

	calculaResultado(Xg, Yg, Xq, Yq, fi, p);
}

void ECC(int Xg, int Yg, int n, int a, int p){
	int aux = 0;
	int *Xq = malloc(sizeof(int));
	int *Yq = malloc(sizeof(int));
	int IG;
	int IQ;

	// Xg = calcula(Xg, p);
	// Yg = calcula(Yg, p);

	*Xq = Xg;
	*Yq = Yg;

	for(aux = 1; aux < n; aux++){
		// Aqui a gente gera a inversa da G seguindo o que estava no AVA
		IG = (p - Yg) % p;
		if(IG < 0)
			IG += p;

		// Aqui a gente gera a inversa da Q seguindo o que estava no AVA
		IQ = (p - *Yq) % p;
		if(IQ < 0)
			IQ += p;

		// Aqui verifica se o G não é vazio (pois caso seja vazio, a soma irá ser o próprio valor definido no Q)
		if(Xg != 0 && Yg != 0){
			// Caso os valores de G não sejam vazio (0) então irá passar o valor de G pra Q
			if((*Xq) == 0 && Yq == 0){
				*Xq = Xg;
				*Yq = Yg;
			// Aqui verifica caso seja igual a inversa
			}else if(((*Xq) == Xg && (*Yq) == IG) || (Xg == (*Xq) && Yg == IQ)){
				*Xq = 0;
				*Yq = 0;
			}else{
				// Caso sejam iguais
				if(Xg == (*Xq) && Yg == (*Yq))
				{
					if(*Yq != 0)
						multiplicaPontos(Xg, Yg, Xq, Yq, p, a);
					else
						*Xq = 0;
				// Caso sejam diferentes
				}else
					somaPontos(Xg, Yg, Xq, Yq, p);
			}
		}
	}
	printf("%d %d\n", *Xq, *Yq);

	free(Xq);
	free(Yq);
}

int main(){
	int Xg, Yg;
	int n, a, p;

	do{
		Xg = 0;
		Yg = 0;
		n = a = p = 0;

		scanf("%d", &n);
		if(n > 0){
			scanf("%d %d %d %d", &a, &p, &Xg, &Yg);
			ECC(Xg, Yg, n, a, p);
		}
	}while(n > 0);

	return 0;
}