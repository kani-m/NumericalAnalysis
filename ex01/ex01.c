#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ex01.h"

float f_rand(void) {
  return (float)rand()/RAND_MAX;
}

uint32_t float_to_u32(float x) {
  uint32_t* p;
  
  p = (uint32_t*)(&x);
  
  return (uint32_t)*p;
}

float u32_to_float(uint32_t x) {
  float* p;

  p = (float*)(&x);

  return (float)*p;
}

uint64_t access(uint64_t x, uint8_t s) {
  uint64_t res;

  res = (x >> s) & 0x1ULL;

  return res;
}

void putbits(uint64_t x, uint8_t n) {
  int8_t i;

  for(i = n-1; i >= 0; i--) {
    if(access(x, i) == 1ULL) {
      printf("1");
    } else {
      printf("0");
    }
  }
  printf("\n");
}
