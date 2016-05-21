// Euclidean Algorithm
// Henrique Teruo Eihara RA: 490016

#include <stdio.h>
#include <stdlib.h>

void extended_gcd(int a, int b){
  int s0 = 1, t0 = 0, s1 = 0, t1 = 1, i = 1;
  int r0 = a, r1 = b, r2;
  int q1;
  int s2, t2;

  do{
    i++;
    r2 = r0 % r1;
    //printf("r2 = %d\n",r2);
    q1 = (r0 - r2)/r1;
    //printf("q1 = %d\n",q1);
    s2 = s0 - q1 * s1;
    //printf("s2 = %d\n",s2);
    t2 = t0 - q1 * t1;
    //printf("t2 = %d\n",t2);
    //printf("---------\n");

    if(r2 == 0)
      break;

    r0 = r1;
    r1 = r2;
    s0 = s1;
    s1 = s2;
    t0 = t1;
    t1 = t2;

  }while(1);

  if(t1 < 0)
    printf("%d\n",t1*(-1));
  else
    printf("%d\n",t1);
}


int gcd(int a, int b){
  if(b == 0){
    return a;
  }else{
    return gcd(b, a % b);
  }
}


int main(){
  int a, b, aux;

//  if(argc != 3){
//    printf("Usage: %s valueA valueB\n",argv[0]);
//    exit(0);
//  }

//  sscanf(argv[1], "%d", &a);
//  sscanf(argv[2], "%d", &b);

  scanf("%d %d", &a, &b);

  if(a < b){
    aux = a;
    a = b;
    b = aux;
  }

  int saida = gcd (a,b);

  printf("%d ",saida);
  if(saida == 1){
    extended_gcd(a,b);
  }else
    printf("N\n");

  return 0;
}
