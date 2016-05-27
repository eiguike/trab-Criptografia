// Square & Multiply with GMP

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define li long int

void sam(mpz_t H,mpz_t base,mpz_t modulus, mpz_t r){

  mpz_mod(base, base, modulus);

  mpz_t mask;
  mpz_init(mask);
  mpz_set_ui(mask,1);

  mpz_t rop;
  mpz_init(rop);

  mpz_set_ui(r,1);

  while(mpz_cmp_ui(H,0) > 0){
    mpz_and(rop, H, mask);
    if(mpz_cmp_ui(rop, 1) == 0){
      mpz_mul(r,r,base);
      mpz_mod(r,r,modulus);
    }
    mpz_mul(base,base,base);
    mpz_mod(base,base,modulus);

    mpz_tdiv_q_2exp(H, H,1); 
  }
}

int main(){
  mpz_t base, H, modulus, result;
  mpz_init(base);
  mpz_init(H);
  mpz_init(modulus);
  mpz_init(result);

  gmp_scanf("%Zd", base);
  gmp_scanf("%Zd", H);
  gmp_scanf("%Zd", modulus);

  sam(H,base,modulus, result);
  gmp_printf("%Zd\n",result);

  return 0;
}
