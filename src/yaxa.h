#ifndef YAXA_H
#define YAXA_H

#include <stdint.h>

enum opcode {
  // TODO
};

enum prefix {
  PREFIX_LOCK = 1 << 0,

  PREFIX_REP   = 1 << 1,
  PREFIX_REPE  = 1 << 2,
  PREFIX_REPNE = 1 << 2,

  PREFIX_SEG_CS = 1 << 3,
  PREFIX_SEG_SS = 1 << 4,
  PREFIX_SEG_DS = 1 << 5,
  PREFIX_SEG_ES = 1 << 6,
  PREFIX_SEG_FS = 1 << 7,
  PREFIX_SEG_GS = 1 << 8,

  PREFIX_OPER_OVERRIDE = 1 << 9,
  PREFIX_ADDR_OVERRIDE = 1 << 10,
};

enum reg {
  AX = 0,
  BX = 3,
  CX = 1,
  DX = 2,
  SI = 6,
  DI = 7,
  BP = 5,
  SP = 4,

  R8 = 8,
  R9,
  R10,
  R11,
  R12,
  R13,
  R14,
  R15,

  // The following registers are weird so we don't just number them
  // as they are in machine code

  CS,
  SS,
  DS,
  ES,
  FS,
  GS,

  AH,
  BH,
  CH,
  DH,
};

struct operand {
  enum {
    IMMEDIATE,
    ADDR,
    REGISTER,
    INDIRECT,
  } type;

  union {
    uint64_t immediate;
    uint64_t addr;
    enum reg reg;
    struct {
      enum reg base;
      enum reg index;
      uint8_t scale;
      uint64_t disp;
    } indirect;
  };
};

enum size {
  BYTE  = 1,
  WORD  = 2,
  DWORD = 4,
  QWORD = 8,
};

struct instruction {
  enum size size;
  uint16_t prefixes;
  enum opcode opcode;
  struct operand a, b;
};

#endif
