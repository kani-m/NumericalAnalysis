#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include "ex01.h"

#define MASK(n) ((0x1UL << (n)) - 0x1UL)

typedef struct {
  uint64_t frac;
  uint16_t exp;
  uint8_t  sign;
} myFloat;

myFloat float_to_myFloat(const   float*);
float   myFloat_to_float(const myFloat*);
void       print_myFloat(const myFloat*);

myFloat      add(const myFloat*, const myFloat*);
myFloat multiply(const myFloat*, const myFloat*);

int main(int argc, char* argv[]) {
  // Declare variables
  float    x,  y,  z,  sol;
  myFloat mx, my, mz, msol;
  double  err;
  int32_t i;

  // Initialize seed of random value
  srand(time(NULL));

  // main part
  // -- (1) --
  for(i = 0; i < 10; i++) {
    x = f_rand();
    y = f_rand();

    mx = float_to_myFloat(&x);
    my = float_to_myFloat(&y);

    mz = multiply(&mx, &my);
    z  = myFloat_to_float(&mz);

    sol = x*y;
    err = fabs((sol - z)/sol);
    printf("result = %11.10e, err = %11.10e\n", z, err);
    if(err > 1e-15) {
      print_myFloat(&mz);

      msol = float_to_myFloat(&sol);
      print_myFloat(&msol);
    }
  }
  
  /*
  // -- test --
  x  = 1.0f;
  mx = float_to_myFloat(&x);
  printFloat(&mx);

  y  = 1.5f;
  my = float_to_myFloat(&y);
  printFloat(&my);

  mz = multiply(&mx, &my);
  z  = myFloat_to_float(&mz);

  printFloat(&mz);
  sol = x*y;
  err = fabs((sol - z)/sol);
  printf("result = %11.10e, err = %11.10e\n", z, err);
  */
  return 0;
}

myFloat float_to_myFloat(const float* p) {
  myFloat mf;
  uint32_t tmp;

  tmp = float_to_u32(*p);

  // Initialize parameter of myFloat
  mf.frac = (tmp & MASK(23)) | (0x1UL << 23);
  mf.exp  = (tmp >> 23) & MASK(8);
  mf.sign = (tmp >> 31) & MASK(1);

  return mf;
}

float myFloat_to_float(const myFloat* mp) {
  float f;
  uint32_t tmp;

  tmp = (mp->sign << 31) | ((mp->exp & MASK(8)) << 23) | (mp->frac & MASK(23));
  f   = u32_to_float(tmp);

  return f;
}

void print_myFloat(const myFloat* mp) {
  printf("% .10e -> \n", myFloat_to_float(mp));
  printf("%20s ", "sign:");
  putbits(mp->sign, 1);
  printf("%20s ", "exp:");
  putbits(mp->exp,  8);
  printf("%20s ", "frac:");
  putbits(mp->frac, 23);
  printf("\n");
}

myFloat add(const myFloat* mp, const myFloat* mq) {
  myFloat mf;

  // Calculation
  
  return mf;
}

myFloat multiply(const myFloat* mp, const myFloat* mq) {
  myFloat mf;

  // Calculation
  mf.sign = mp->sign ^ mq->sign;
  mf.frac = mp->frac * mq->frac;
  mf.exp  = mp->exp  + mq->exp - 127;

  if(mf.exp >> 8) {
    // Overflow exception
    mf.frac = 0;
    mf.exp  = MASK(8);
  }

  if(mf.frac >> 47) {
    mf.frac = (mf.frac & MASK(47)) >> 24;
    mf.exp += 1;
  } else if(mf.frac >> 46) {
    mf.frac = (mf.frac & MASK(46)) >> 23;
  }
  
  return mf;
}
