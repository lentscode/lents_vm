#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdint.h>

#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX];

enum { MR_KBSR = 0xfe00, MR_KBDR = 0xfe02 };

void mem_write(uint16_t address, uint16_t val);
uint16_t mem_read(uint16_t address);
uint16_t check_key();

#endif