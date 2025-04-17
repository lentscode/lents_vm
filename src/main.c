#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "memory.h"
#include "registers.h"
#include "system.h"
#include "utils.h"

extern uint16_t reg[R_COUNT];

extern struct termios original_tio;

int main(int argc, char **argv) {
  signal(SIGINT, handle_interrupt);
  disable_input_buffering();

  if (argc < 2) {
    /* show usage string */
    printf("lc3 [image-file1] ...\n");
    return 2;
  }

  for (size_t j = 1; j < argc; j++) {
    printf("Loading image file: %s\n", argv[j]);
    if (!read_image(argv[j])) {
      printf("failed to load image: %s\n", argv[j]);
      return EXIT_FAILURE;
    }
    printf("Image loaded successfully\n");
  }

  reg[R_COND] = FL_ZRO;

  enum { PC_START = 0x3000 };
  reg[R_PC] = PC_START;
  printf("Starting execution at PC = 0x%04x\n", reg[R_PC]);

  int running = 1;
  while (running) {
    uint16_t instr = mem_read(reg[R_PC]++);
    uint16_t op = instr >> 12;

    switch (op) {
    case OP_ADD:
      handle_add(instr);
      break;
    case OP_AND:
      handle_and(instr);
      break;
    case OP_NOT:
      handle_not(instr);
      break;
    case OP_BR:
      handle_br(instr);
      break;
    case OP_JMP:
      handle_jmp(instr);
      break;
    case OP_JSR:
      handle_jsr(instr);
      break;
    case OP_LD:
      handle_ld(instr);
      break;
    case OP_LDI:
      handle_ldi(instr);
      break;
    case OP_LDR:
      handle_ldr(instr);
      break;
    case OP_LEA:
      handle_lea(instr);
      break;
    case OP_ST:
      handle_st(instr);
      break;
    case OP_STI:
      handle_sti(instr);
      break;
    case OP_STR:
      handle_str(instr);
      break;
    case OP_TRAP:
      handle_trap(instr);
      // Check if we need to halt
      if ((instr & 0xff) == TRAP_HALT) {
        running = 0;
      }
      break;
    case OP_RES:
      handle_res(instr);
      break;
    case OP_RTI:
      handle_rti(instr);
      break;
    default:
      abort();
      break;
    }
  }

  restore_input_buffering();

  return EXIT_SUCCESS;
}