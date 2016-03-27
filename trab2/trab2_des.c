#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>

// cifragem em bloco

int main(){

  // receber o bloco de 64 bits
  // realizar a permutação inicial
  // dividir o bloco em 32 bits (L0 e R0)
  // passar como parametro para função f (R0)
  // a saída dessa função é feita a operação XOR com L0

  // entrada para ser cifrada e decifrada
  // l = 154 i = 151 f = 146 e = 145
  // w = 167 j = 152 o = 157 y = 171
  unsigned char input[8] = "lifewjoy";

  unsigned int left = 0;
  unsigned int right = 0;

  char * pointer;
  int i;
  int i2;


  // laço que divide os bits de input
  // para os int left e right
  for(i=0;i<8;i++){
    printf("%x INPUT\n",input[i]);

    if(i<4){
      // left
      left |= input[i] << (i*8);
    }else{
      right |= input[i] << ((i-4)*8);
    }

    //printf("RESULTADO:\n");
    //pointer = (char*)(&left);
    //for(i2=0;i2<4;i2++)
      //printf("%x ",pointer[i2]);
    //printf("\n");
  }

}

