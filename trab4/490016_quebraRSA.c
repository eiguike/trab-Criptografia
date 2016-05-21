// Quebra do RSA
// Henrique Teruo Eihara RA: 490016

#include <stdio.h>
#include <stdlib.h>

#define lli long long int
#define DEBUG 0

int tam = 0;

// encontra os fatores de primos
int * factor(int n){
  int * ret = malloc(sizeof(int)*tam);

  // primeiro primo
  int p = 2;
  int prime, div;
  int flag = 0;

  // fatoração de primos
  while(n >1){
    flag = 0;
    // realiza a fatoração
    while(n % p == 0){
      n = n / p;
      flag = 1;
    }

    if(flag == 1){
      tam++;
      ret = realloc(ret, sizeof(int)*tam);
      ret[tam-1] = p;
    }

    // descobre outro primo possível para fatorar
    do{
      if(p == 2)
        p+=1;
      else
        p+=2; // não existe outro número primo par

      // inicializa variáveis
      prime = 1; div = 2;

      // laço que descobre se o número não é primo
      while((div <= (p/2))){
        // se não for primo, tenta outro numero
        if (p % div==0){
          prime = 0;
          break;
        }else
          div = div + 1;
      }
    }while(!prime);
    prime = 0;
  }

  return ret;
}

// quadrado & multiplicação
lli sam(lli H, lli base, lli modulus){
  base = base % modulus;
  lli r = 1;

  while(H > 0){
    if((H & 0x1)==1){
      r = (r*base)%modulus;
    }
    base = (base*base)%modulus;
    H >>=1;
  }

  return r;
}

int extended_gcd(int a, int b){
  int s0 = 1, t0 = 0, s1 = 0, t1 = 1, i = 1;
  int r0 = a, r1 = b, r2;
  int q1;
  int s2, t2;

  do{
    i++;
    r2 = r0 % r1;
    q1 = (r0 - r2)/r1;
    s2 = s0 - q1 * s1;
    t2 = t0 - q1 * t1;

    if(r0%r1 == 0)
      break;

    r0 = r1;
    r1 = r2;
    s0 = s1;
    s1 = s2;
    t0 = t1;
    t1 = t2;
  }while(1);


  if(r1 == 1){
    // tratando caso quando o inverso for negativo
    if(t1 < 0){
      return t1 + a;
    }else{
      return t1;
    }
  }
  return 0;
}

int main(int argc, char * argv[]){
  int n, e, c;
  int * semiprimes = NULL;

  scanf("%d %d %d", &n, &e, &c);

  // factor retorna os números primos da fatoração
  semiprimes = factor(n);

  // os últimos números primos gerados são os maiores
  int p = semiprimes[tam-1];
  int q = semiprimes[tam-2];

  int totiente = (p-1) * (q-1);

  int D;
  if(totiente >= e)
    D = extended_gcd(totiente,e);
  else
    D = extended_gcd(e,totiente);

  lli result = sam(D,c,n);

  printf("%lld\n",result);

  // livrando a memória
  free(semiprimes);

  return 0;
}
