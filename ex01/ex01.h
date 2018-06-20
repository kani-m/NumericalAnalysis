#ifndef _EX01_H_
#define _EX01_H_

#include <stdint.h>

float          f_rand(void);
uint32_t float_to_u32(float);
float    u32_to_float(uint32_t);
uint64_t       access(uint64_t, uint8_t);
void          putbits(uint64_t, uint8_t);

#endif /* Not def: _EX01_H_ */
