#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "squareMultiply.c"

// Decriptografar a mensagem C utilizando N e D (onde D é a chave secreta):
// M = C^D (mod N)
// Criptografar a mensagem M utilizando N e E (onde E é a chave pública*):
// C = M^E (mod N)
// * É a chave pública mas também pode ser a secreta, porém nesse caso utilizaremos apenas como pública

// Usage: <programName.c> <1:create keys - 0:inform keys> <c:crypt - d:decrypt> <plain/cypherTXT> <optional:base (default: 10)>

int main(int argc, char *argv[]){
  int base;
  long long int N, publicK, secretK;
  mpz_t modulus, expoent, textIn, result;
  mpz_inits(modulus, expoent, textIn, result, NULL);

  if(argc == 5)
    base = argv[4];
  else
    base = 10;

  mpz_set_str(textIn, argv[3], base);

  // Seleciona se a escolha foi criar as chaves ou informar
  if(argv[1] == 1){
    generateK(&N, &publicK, &secretK);
    printf("Public Key generated: %llu\n", publicK);
    printf("Secret Key generated: %llu\n", secretK);
    mpz_set_ui(modulus, N);
    if(argv[2] == 'c')
      mpz_set_ui(expoent, publicK);
    else
      mpz_set_ui(expoent, secretK);
  }else{
    if(base == 16){
      gmp_scanf("%Zx", modulus);
      gmp_scanf("%Zx", expoent);
    }else{
      gmp_scanf("%Zd", modulus);
      gmp_scanf("%Zd", expoent);
    }
  }

  sam(expoent, textIn, modulus, result);

  if(base == 16)
    gmp_printf("%Zx\n", result);
  else
    gmp_printf("%Zd\n", result);

  mpz_clears(modulus, expoent, textIn, result, NULL);
}

void generateK(long long int *N, long long int *publicK, long long int *secretK){
  
}