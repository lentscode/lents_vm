#include <stdio.h>

#include "commands.h"
#include "memory.h"
#include "registers.h"
#include "utils.h"

void handle_add(uint16_t instr) {
  uint16_t r0 = (instr >> 9) & 0x7;
  uint16_t r1 = (instr >> 6) & 0x7;
  uint16_t imm_flag = (instr >> 5) & 0x1;

  if (imm_flag) {
    uint16_t imm5 = sign_extend(instr & 0x1f, 5);
    reg[r0] = reg[r1] + imm5;
  } else {
    uint16_t r2 = instr & 0x7;
    reg[r0] = reg[r1] + reg[r2];
  }

  update_flags(r0);
}

void handle_and(uint16_t instr) {
  uint16_t r0 = (instr >> 9) & 0x7;
  uint16_t r1 = (instr >> 6) & 0x7;
  uint16_t imm_flag = (instr >> 5) & 0x1;

  if (imm_flag) {
    uint16_t imm5 = sign_extend(instr & 0x1f, 5);
    reg[r0] = reg[r1] & imm5;
  } else {
    uint16_t r2 = instr & 0x7;
    reg[r0] = reg[r1] & reg[r2];
  }

  update_flags(r0);
}

void handle_not(uint16_t instr) {
  uint16_t r0 = (instr >> 9) & 0x7;
  uint16_t r1 = (instr >> 6) & 0x7;

  reg[r0] = ~reg[r1];
  update_flags(r0);
}

void handle_br(uint16_t instr) {
  uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);
  uint16_t cond_flag = (instr >> 9) & 0x7;
  if (cond_flag & reg[R_COND]) {
    reg[R_PC] += pc_offset;
  }
}

void handle_jmp(uint16_t instr) {
  uint16_t r1 = (instr >> 6) & 0x7;
  reg[R_PC] = reg[r1];
}

void handle_jsr(uint16_t instr) {
  reg[R_R7] = reg[R_PC];

  uint16_t flag = (instr >> 11) & 0x1;
  if (flag) {
    uint16_t pc_offset = sign_extend(instr & 0x7ff, 11);
    reg[R_PC] += pc_offset;
  } else {
    uint16_t r0 = (instr >> 6) & 0x7;
    reg[R_PC] = reg[r0];
  }
}

void handle_ld(uint16_t instr) {
  uint16_t r0 = (instr >> 9) & 0x7;
  uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

  reg[r0] = mem_read(reg[R_PC] + pc_offset);
  update_flags(r0);
}

void handle_ldi(uint16_t instr) {
  uint16_t r0 = (instr >> 9) & 0x7;
  uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

  reg[r0] = mem_read(mem_read(reg[R_PC] + pc_offset));
  update_flags(r0);
}

void handle_ldr(uint16_t instr) {
  uint16_t r0 = (instr >> 9) & 0x7;
  uint16_t r1 = (instr >> 6) & 0x7;
  uint16_t pc_offset = sign_extend(instr & 0x3f, 6);

  reg[r0] = mem_read(reg[r1] + pc_offset);
  update_flags(r0);
}

void handle_lea(uint16_t instr) {
  uint16_t r0 = (instr >> 9) & 0x7;
  uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

  reg[r0] = reg[R_PC] + pc_offset;
  update_flags(r0);
}

void handle_st(uint16_t instr) {
  uint16_t r1 = (instr >> 9) & 0x7;
  uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

  mem_write(reg[R_PC] + pc_offset, reg[r1]);
}

void handle_sti(uint16_t instr) {
  uint16_t r1 = (instr >> 9) & 0x7;
  uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

  mem_write(mem_read(reg[R_PC] + pc_offset), reg[r1]);
}

void handle_str(uint16_t instr) {
  uint16_t r0 = (instr >> 9) & 0x7;
  uint16_t r1 = (instr >> 6) & 0x7;
  uint16_t pc_offset = sign_extend(instr & 0x3f, 6);

  mem_write(reg[r1] + pc_offset, reg[r0]);
}

void handle_trap(uint16_t instr) {
  reg[R_R7] = reg[R_PC];

  switch (instr & 0xff) {
  case TRAP_GETC: {
    reg[R_R0] = (uint16_t)getchar();
    update_flags(R_R0);
    break;
  }
  case TRAP_OUT: {
    putc((char)reg[R_R0], stdout);
    fflush(stdout);
    break;
  }
  case TRAP_PUTS: {
    uint16_t *c = memory + reg[R_R0];

    while (*c) {
      putc((char)*c, stdout);
      ++c;
    }

    fflush(stdout);
    break;
  }
  case TRAP_IN: {
    printf("Enter a character > ");
    char c = getchar();
    putc(c, stdout);
    fflush(stdout);
    reg[R_R0] = (uint16_t)c;
    update_flags(R_R0);
    break;
  }
  case TRAP_PUTSP: {
    uint16_t *c = memory + reg[R_R0];
    while (*c) {
      char char1 = (*c) & 0xff;
      putc(char1, stdout);
      char char2 = (*c) >> 8;
      if (char2)
        putc(char2, stdout);
      ++c;
    }
    break;
  }
  case TRAP_HALT: {
    puts("HALT");
    fflush(stdout);
    // We'll handle the halt in the main function
    break;
  }
  }
}

void handle_res(uint16_t instr) {
  // Reserved instruction, do nothing
}

void handle_rti(uint16_t instr) {
  // RTI instruction, do nothing
}