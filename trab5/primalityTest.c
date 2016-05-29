// Primality Test with GMP

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define FALSE 0
#define TRUE 1

int primalityTest(mpz_t result, mpz_t n){
  if(mpz_cmp_ui(n,1) <= 0){
    return FALSE;
  }else if(mpz_cmp_ui(n,3) <= 0){
    return TRUE;
  }else{
    mpz_mod_ui(result, n, 2);
    if(mpz_cmp_ui(result,0) == 0){
      return FALSE;
    }
    mpz_mod_ui(result, n, 3);
    if(mpz_cmp_ui(result,0) == 0){
      return FALSE;
    }
  }

  mpz_t i;
  mpz_init(i);
  mpz_set_ui(i,5);

  while(mpz_mul(result, i, i), mpz_cmp(result,n) <= 0){
    if(mpz_mod(result,n,i), mpz_cmp_ui(result,0)==0){
      return FALSE;
    }
    mpz_add_ui(i,i,2);
    if(mpz_mod(result,n,i), mpz_cmp_ui(result,0) ==0){
      return FALSE;
    }
    mpz_add_ui(i,i,6);
  }

  mpz_clear(i);

  return TRUE;
}

/*
int main(){
  mpz_t N;
  mpz_t result;

  mpz_inits(N,result);

  gmp_scanf("%Zd",N);

  if(primalityTest(result, N) == 1){
    printf("É primo\n");
  }else{
    printf("Não é primo\n");
  }

  mpz_clear(N);
  mpz_clear(result);
}
*/
