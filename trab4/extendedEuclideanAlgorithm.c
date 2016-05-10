// Quebra do RSA
// Henrique Teruo Eihara RA: 490016

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define lgii long long int
#define DEBUG 0

// h = expoente
// base = base
// modulus = modulus
lgii sam(lgii H, lgii base, lgii modulus){
  int i;
  int marcador = 0;
  lgii y = base;

  // conta quantos bits tem no número
  for(i=0;i<64;i++){
    if((H>>i)& 0x1){
      marcador = i;
    }
  }

  if(DEBUG)
    printf("Marcador: %d\n",marcador);

  // realiza o square-and-multiply
  for(i=0;i<marcador;i++){
    if(DEBUG)
      printf("Resultado: %lld\n",y);

    y = (y*y) % modulus;
    if(((H>>i)&0x1)==0x1){
      y = (y*base) % modulus;
      if(DEBUG)
        printf("1 squares the equation and then multiplies by the number\n");
    }else if(DEBUG)
      printf("0 squares the equation\n");
  }

  if(DEBUG)
    printf("Resultado: %lld\n",y);

  return y;
}

void extended_gcd(int a, int b, int *rRet, int * sRet, int * tRet){
  int s0 = 1, t0 = 0, s1 = 0, t1 = 1;
  int r0 = b, r1 = a;
  int aux;
  int q;

  while(r0 != 0){
    q = r1/r0;
    aux = r1; r1 = r0;
    r0 = aux - q * r0;

    aux = s1; s1 = s0;
    s0 = aux - q * s0;

    aux = t1; t1 = t0;
    t0 = aux - q * t0;
  }

  *rRet = r1;
  *sRet = s1;
  *tRet = t1;
}

// semi primos para n
// dois p e q, dps tira o totiente
// inversa do e com o totiente
// b sempre maior q a

int main(int argc, char * argv[]){
  int n, e, c;

  scanf("%d %d %d", &n, &e, &c);

  lgii aux = floor(sqrt(n));

  printf("aux = %lld\n",aux);
  if(aux % 2 == 0)
    aux--;
  aux+=2;
  printf("aux = %lld\n",aux);

  do{
    aux -= 2;
  }while(n%aux!=0);
  printf("aux = %lld\n",aux);

  lgii p = aux;
  lgii q = n/p;

  printf("%d\n",e);

  double d = (1/(float)(e)) % ((p-1)*(q-1));
  printf("%f\n",d);

  printf("%f %d %d\n",d,c,e);

  printf("mensagem original: %lld\n",sam(d,c,e));

  return 0;
}
