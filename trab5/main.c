#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "squareMultiply.c"

int main(){
  int base;
  mpz_t modulus, expoent, plainText, cipherText, result;
  mpz_inits(modulus, expoent, plainText, cipherText,result, NULL);

  scanf("%d", &base);

  if(base == 16){
    gmp_scanf("%Zx", modulus);
    gmp_scanf("%Zx", expoent);
    gmp_scanf("%Zx", plainText);
    gmp_scanf("%Zx", cipherText);
  }else{
    gmp_scanf("%Zd", modulus);
    gmp_scanf("%Zd", expoent);
    gmp_scanf("%Zd", plainText);
    gmp_scanf("%Zd", cipherText);
  }

  sam(expoent, plainText, modulus, result);

  if(base == 16)
    gmp_printf("%Zx\n", result);
  else
    gmp_printf("%Zd\n", result);

  if(mpz_cmp(cipherText, result) == 0){
    printf("It is equal\n");
  }else{
    printf("something went wrong\n");
  }

  mpz_clears(modulus, expoent, plainText, cipherText, result, NULL);

}
