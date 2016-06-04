#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

#include <math.h>

#include "squareMultiply.c"

int keyLength;

typedef struct{
  mpz_t n; // modulus n
  mpz_t e; // public expoent
  mpz_t d; // private expoent
  mpz_t p; // prime p
  mpz_t q; // prime q
} Key;

// Decriptografar a mensagem C utilizando N e D (onde D é a chave secreta):
// M = C^D (mod N)
// Criptografar a mensagem M utilizando N e E (onde E é a chave pública*):
// C = M^E (mod N)
// * É a chave pública mas também pode ser a secreta, porém nesse caso utilizaremos apenas como pública

// Usage: <programName.c> <1:create keys - 0:inform keys> <c:crypt - d:decrypt> <plain/cypherTXT> <optional:base (default: 10)>
void generateKeys(Key * k);

int main(){
  int base;

  printf("10 - Decimal\n 16 - Hexadecimal\n Your choose: ");
  scanf("%d",&base);

  if((base != 10)&&(base!= 16))
    exit(0);

  printf("1 - 512 key length\n");
  printf("2 - 1024 key length\n");
  printf("3 - 2048 key length\n");
  printf("Your choose: ");

  scanf("%d",&keyLength);

  switch(keyLength){
    case 1:
      keyLength = 512;
      break;
    case 2:
      keyLength = 1024;
      break;
    case 3:
      keyLength = 2048;
      break;
    default:
      exit(0);
      break;
  }

  Key key;
  mpz_inits(key.n, key.e, key.d, key.p, key.q, NULL);

  mpz_t textIn, result, result2;
  mpz_inits(textIn, result, result2, NULL);

  generateKeys(&key);

  gmp_printf("Modulus: %Zd\n", key.n);
  if(base == 16){
    gmp_printf("Public Key generated: %Zx\n", key.e);
    gmp_printf("Secret Key generated: %Zx\n", key.d);
    gmp_scanf("%Zx",textIn);
  }else{
    gmp_printf("Public Key generated: %Zd\n", key.e);
    gmp_printf("Secret Key generated: %Zd\n", key.d);
    gmp_scanf("%Zd",textIn);
  }

  // creating a message
  //gmp_randstate_t state;
  //gmp_randinit_default(state);

  // ecrypting
  sam(key.e, textIn, key.n, result);

  // decrypting
  sam(key.d, result, key.n, result2);

  if(base == 16){
    printf("-------------------------ENCRYPT MESSAGE--------------------------");
    gmp_printf("%Zx\n", result);
    printf("-------------------------DECRYPT MESSAGE--------------------------");
    gmp_printf("%Zx\n", result);
  }else{
    printf("-------------------------ENCRYPT MESSAGE--------------------------");
    gmp_printf("%Zd\n", result);
    printf("-------------------------DECRYPT MESSAGE--------------------------");
    gmp_printf("%Zd\n", result);
  }

  mpz_clears(key.n, key.e, key.d, key.p, key.q, textIn, result, result2, NULL);
}

void generateKeys(Key * k){
  // generating p
  gmp_randstate_t state;
  gmp_randinit_default(state);

  mpz_t aux, aux2, mask;
  mpz_inits(aux, aux2, mask, NULL);
  mpz_set_ui(aux2,1);

  // setting a large number in p
  mpz_mul_2exp(aux2, aux2, (keyLength/2)-1);

  mpz_urandomb(aux, state, keyLength/2);
  mpz_add(aux, aux2, aux);

  mpz_set(mask, aux); // saving the value
  mpz_nextprime(k->p, aux);

  mpz_mod(aux2, k->p, k->e);
  while(mpz_cmp_ui(aux2, 1) == 0){
    mpz_nextprime(k->p, aux);
    mpz_mod(aux2, k->p, k->e);
  }

  gmp_printf("P: %Zd\n", k->p);

  // choosing now prime number for q
  do{
    mpz_set_ui(aux2,1);
    // setting a large number in q
    mpz_mul_2exp(aux2, aux2, (keyLength/2)-1);
    mpz_urandomb(aux, state, keyLength/2);
    mpz_add(aux, aux2, aux);
    mpz_set(mask, aux); // saving the value
    mpz_nextprime(k->q, aux);
    mpz_mod(aux2, k->q, k->e);
    while(mpz_cmp_ui(aux2, 1) == 0){
      mpz_nextprime(k->q, aux);
      mpz_mod(aux2, k->q, k->e);
    }
  }while(mpz_cmp(k->p, k->q) == 0);

  gmp_printf("Q: %Zd\n", k->q);

  mpz_mul(k->n, k->p, k->q);

  mpz_t totiente;
  mpz_init(totiente);

  mpz_sub_ui(aux, k->p, 1);
  mpz_sub_ui(aux2, k->q, 1);
  mpz_mul(totiente, aux2, aux);

  mpz_set_ui(aux2, 0);
  mpz_nextprime(aux2, aux2);

  while(mpz_gcd(aux, totiente, aux2), mpz_cmp_ui(aux,1) != 0 ){
    mpz_nextprime(aux2,aux2);
  }

  mpz_invert(k->d, k->e, totiente);
  gmp_printf("k->d: %Zd\n", k->d);
  gmp_printf("k->d: %Zd\n", k->d);

}
