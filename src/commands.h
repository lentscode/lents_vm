#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

enum {
  OP_BR = 0, /* branch */
  OP_ADD,    /* add  */
  OP_LD,     /* load */
  OP_ST,     /* store */
  OP_JSR,    /* jump register */
  OP_AND,    /* bitwise and */
  OP_LDR,    /* load register */
  OP_STR,    /* store register */
  OP_RTI,    /* unused */
  OP_NOT,    /* bitwise not */
  OP_LDI,    /* load indirect */
  OP_STI,    /* store indirect */
  OP_JMP,    /* jump */
  OP_RES,    /* reserved (unused) */
  OP_LEA,    /* load effective address */
  OP_TRAP    /* execute trap */
};

enum {
  FL_POS = 1 << 0, /* P */
  FL_ZRO = 1 << 1, /* Z */
  FL_NEG = 1 << 2, /* N */
};

enum {
  TRAP_GETC =
      0x20, /* get character from keyboard, not echoed onto the terminal */
  TRAP_OUT = 0x21,   /* output a character */
  TRAP_PUTS = 0x22,  /* output a word string */
  TRAP_IN = 0x23,    /* get character from keyboard, echoed onto the terminal */
  TRAP_PUTSP = 0x24, /* output a byte string */
  TRAP_HALT = 0x25   /* halt the program */
};

// Function declarations for each instruction
void handle_add(uint16_t instr);
void handle_and(uint16_t instr);
void handle_not(uint16_t instr);
void handle_br(uint16_t instr);
void handle_jmp(uint16_t instr);
void handle_jsr(uint16_t instr);
void handle_ld(uint16_t instr);
void handle_ldi(uint16_t instr);
void handle_ldr(uint16_t instr);
void handle_lea(uint16_t instr);
void handle_st(uint16_t instr);
void handle_sti(uint16_t instr);
void handle_str(uint16_t instr);
void handle_trap(uint16_t instr);
void handle_res(uint16_t instr);
void handle_rti(uint16_t instr);

#endif