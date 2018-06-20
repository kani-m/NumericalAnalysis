#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "ex01.h"

typedef union {
  struct {
    uint32_t frac : 23;
    uint16_t exp  :  8;
    uint8_t  sign :  1;
  } body;
  float face;
} Float;

void printFloat(Float);

int main() {
  Float x, y;

  srand(time(NULL));
  
  x.face = 2.0f*f_rand() - 1.0f;
  y.face = 1.5f;

  printFloat(x);
  printFloat(y);

  y.body.exp += 1;
  printFloat(y);
  
  return 0;
}

void printFloat(Float x) {
  printf("% .6f -> \n", x.face);
  printf("%12s ", "sign:");
  putbits(x.body.sign, 1);
  printf("%12s ", "exp:");
  putbits(x.body.exp,  8);
  printf("%12s ", "frac:");
  putbits(x.body.frac, 23);
  printf("\n");
}
