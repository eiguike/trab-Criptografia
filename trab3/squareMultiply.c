// Square & Multiply

#include <stdio.h>
#include <stdlib.h>

#define lli long long int

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

int main(int argc, char * argv[]){
  if(argc != 3){
    printf("Usage %s <base> <expoent> <modulus>\n", argv[0]);
    exit(0);
  }

  lli H, base, modulus;
  sscanf(argv[1], "%lld", &H);
  sscanf(argv[2], "%lld", &base);
  sscanf(argv[3], "%lld", &modulus);

  printf("%lld\n",sam(H,base,modulus));

  return 0;
}
