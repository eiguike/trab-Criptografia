#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trab2_desPC.c"

const int ip[64] = {
  58, 50, 42, 34, 26, 18, 10, 2,
  60, 52, 44, 36, 28, 20, 12, 4,
  62, 54, 46, 38, 30, 22, 14, 6,
  64, 56, 48, 40, 32, 24, 16, 8,
  57, 49, 41, 33, 25, 17,  9, 1,
  59, 51, 43, 35, 27, 19, 11, 3,
  61, 53, 45, 37, 29, 21, 13, 5,
  63, 55, 47, 39, 31, 23, 15, 7
};

const int ip2[64] = {
  40, 8, 48, 16, 56, 24, 64, 32,
  39, 7, 47, 15, 55, 23, 63, 31,
  38, 6, 46, 14, 54, 22, 62, 30,
  37, 5, 45, 13, 53, 21, 61, 29,
  36, 4, 44, 12, 52, 20, 60, 28,
  35, 3, 43, 11, 51, 19, 59, 27,
  34, 2, 42, 10, 50, 18, 58, 26,
  33, 1, 41, 9, 49, 17, 57, 25,
};

const int permutationE[48] = {
  32,  1,  2,  3,  4,  5,
   4,  5,  6,  7,  8,  9,
   8,  9, 10, 11, 12, 13,
  12, 13, 14, 15, 16, 17,
  16, 17, 18, 19, 20, 21,
  20, 21, 22, 23, 24, 25,
  24, 25, 26, 27, 28, 29,
  28, 29, 30, 31, 32,  1
};

// sboxes
const int S[8][64] = {{
    //S1
    14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
     0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
     4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
},{
    //S2
    15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
     3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
     0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
},{
    //S3
    10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
    13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
    13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
     1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
},{
     //S4
     7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
    13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
    10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
     3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
},{
    //S5
     2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
    14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
     4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
    11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
},{
    //S6
    12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
    10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
     9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
     4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
},{
     //S7
     4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
    13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
     1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
     6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
},{
    //S8
    13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
     1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
     7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
     2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
}};

// tabela utilizada dps da sbox
const int permutationP[32] = {
  16,  7, 20, 21, 29, 12, 28, 17,
   1, 15, 23, 26,  5, 18, 31, 10,
   2,  8, 24, 14, 32, 27,  3,  9,
  19, 13, 30,  6, 22, 11,  4, 25
};

// tem como entrada a cadeia que precisa ser permutada e flag,
// o laço tem como intenção, alimentar a cadeia resultado
// de forma incremental, no caso, bit a bit. quando é inserido
// um bit, no começo do laço é feito um << 1, para que
// um novo bit possa assumir o lugar
unsigned long long int IFPermutation(const unsigned long long int entrada, int flag){
  unsigned long long int resultado = 0;
  unsigned long long int bitIsolador = 0x0000000000000001;

  int i;

  for(i=0;i<64;i++){
    resultado <<= 1;
    if(!flag)
      resultado |= ((entrada >> (64-ip[i])) & bitIsolador);
    else
      resultado |= ((entrada >> (64-ip2[i])) & bitIsolador);
  }

  return resultado;
}

unsigned long long int fFunction(const unsigned long long int entrada, int round){
  unsigned long long int resultado = 0;
  unsigned long long int bitIsolador = 0x0000000000000001;

  int i;
  for(i=0;i<48;i++){
    resultado<<=1;
    resultado |= ((entrada >> (32-permutationE[i])) & bitIsolador);
  }

  return resultado ^ keys[round];
}

// faz a sboxes e realiza já a apermutação P
unsigned long long int sBoxes(const unsigned long long int entrada){
  unsigned long long int aux = 0;
  unsigned long long int resultado = 0;
  unsigned int linha = 0;
  unsigned int coluna = 0;

  int i;
  int i2;

  aux = entrada;
  aux = (aux << 6) | (aux >> (48 - 6));
  // SBOX1 TEM COMO ENTRADA OS MSB (MOST SIGNIFICANT BIT)
  // portanto foi utilizado um shift cyclic
  for(i=0;i<8;i++){
    // definindo linha e coluna da tabela do sbox
    coluna = ((aux & 0x3E) >> 1) & 0xF;
    linha = (((aux & 0x20) >> 4) | (aux & 0x1)) & 0x3;

    // adquirindo o resultado e jogando na cadeia de bits
    resultado |= (S[i][coluna+(linha*16)]);

    // caso for a última iteração, não faça
    if(i != 7)
      resultado <<= 4;

    // mudando a cadeia de bits para mudar a sbox tbm
    aux = (aux << 6) | (aux >> (48 - 6));
    //printf("SBox %d: ",i);
    //printH((char*)&resultado);
  }

  // realizando a permutação P
  aux = 0;
  for(i2=0;i2<32;i2++){
    aux <<= 1;
    aux |= ((resultado >> (32-permutationP[i2])) & 0x1);
  }

  //printf("Permutação: ");
  //printH((char*)&aux);

  return aux;
}


int main(){
  unsigned long long int entrada = 0xfc1508b214012305;
  unsigned long long int chave = 0x3b3898371520f75e;
  unsigned long long int aux;
  unsigned long long int aux2;
  unsigned long long int aux3;
  unsigned long long int left = 0;
  unsigned long long int right = 0;

  scanf("%llx",&entrada);
  scanf("%llx",&chave);

  printf("Entrada: \t");
  printH((unsigned char*)&entrada);
  printf("Chave Inicial: \t");
  printH((unsigned char*)&chave);
  printf("\n");

  int i;

  // passando a chave como parametro
  // para geração das chaves das rodadads
  keySchedule(chave);

  // aqui é preciso realizar a permutação inicial
  aux = IFPermutation(entrada,0);
  printf("Permutação Inicial: \t");
  printH((unsigned char*)&aux);
  printf("\n");

  // divisão de bits L e R
  left = (aux >> 32) & 0xFFFFFFFF;
  //printH((char*)&left);
  right = aux & 0xFFFFFFFF;
  //printH((char*)&right);

  for(i=0;i<16;i++){
    aux3 = left;
    aux3 <<= 32;
    aux3 |= right;

    // devemos usar a função f e passar como parametro
    // a cadeia de bits R, além da chave transformada
    // no caso, não necessário pq keys é variável global
    aux = fFunction(right, i);
    aux2 = sBoxes(aux);

    // realizando um xor com a saída da função f
    left ^= aux2;

    // trocando de lado
    aux = left;
    left = right;
    right = aux;

    printf("Round %d:\n",i+1);
    printf("Parcial: \t");
    printH((unsigned char*)&aux3);
    printf("Chave: \t\t");
    printH((unsigned char*)&keys[i]);
    printf("\n");
  }

  //terminado os 16 rounds, deve-se realizar a última permutação
  right <<= 32;
  right |= left;

  aux = IFPermutation(right, 1);

  printf("Resultado Criptográfico: \t");
  printH((unsigned char*)&aux);
}

