#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

uint16_t swap16(uint16_t x);
uint16_t sign_extend(uint16_t x, int bit_count);
void update_flags(uint16_t r);

#endif