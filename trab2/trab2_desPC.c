#include <stdio.h>
#include <stdlib.h>

// chaves geradas dps de PC2, durante as rodadas
unsigned long long int keys[16] = {0};

// esquerdo e direito da chave dps de PC1
unsigned long long int c[17], d[17];

// tabela de permutação PC1
const int pc[] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

// tabela de permutação PC2
const char pc2[] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// imprime em formato hexadecimal
// uma cadeia de bits
void printH(const unsigned  char * input){
  int i;
  printf("0x");
  for(i=7;i>=0;i--)
    printf("%02X",input[i]);
  printf("\n");
}

// realiza a permutçaão PC1 e PC2
unsigned long long int permutedKey(unsigned long long int entrada, int flag){
  unsigned long long int resultado = 0;
  unsigned long long int bitIsolador = 0x0000000000000001;

  int i;
  int i2 = (flag == 0 ? 56 : 48);
  for(i=0;i<i2;i++){
      resultado <<= 1;
      if(!flag)
        resultado |= ((entrada >> (64 - pc[i])) & bitIsolador);
      else
        resultado |= ((entrada >> (56 - pc2[i])) & bitIsolador);
  }

  return resultado;
}

// função que realiza a parte de permutação de chaves
// entre as 16 rodadas
void keySchedule(unsigned long long int input){
  unsigned long long int aux;
  int i;

  aux = permutedKey(input, 0);

  printf("Chave Permutada: \t");
  printH((unsigned char*)&aux);

  // dividindo em c e d a chave permutada
  d[0] = aux & 0xFFFFFFF;
  c[0] = (aux >> 28) & 0xFFFFFFF;

  // realizando as 16 rodadas
  for(i=1;i<17;i++){
   switch (i){
      case 1:
      case 2:
      case 9:
      case 16:
        c[i] = (c[i-1] << 1) | (c[i-1] >> (28 - 1));
        d[i] = (d[i-1] << 1) | (d[i-1] >> (28 - 1));
        break;
      default:
        c[i] = (c[i-1] << 2) | (c[i-1] >> (28 - 2));
        d[i] = (d[i-1] << 2) | (d[i-1] >> (28 - 2));
        break;
    }
    // dividindo os bits
    aux = 0;
    aux = 0xFFFFFFF & c[i];
    aux <<= 28;
    aux |= (0xFFFFFFF & d[i]);

    keys[i-1] = permutedKey(aux, 1);
  }
}
