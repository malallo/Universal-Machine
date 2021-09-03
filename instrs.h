#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "assert.h"
#include "mem-infra.h"

//Opcode 0, Conditional move
void cond_mov(uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC);
//Opcode 1, Segmented Load
void seg_load(Mem_T m, uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC);
//Opcode 2, Segmented Store
void seg_store(Mem_T m, uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC);
//Opcode 3, Addition
void add(uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC);
//Opcode 4, Multiplication
void mult(uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC);
//Opcode 5, Division
void div_i(uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC);
//Opcode 6, Bitwise NAND
void nand(uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC);
//Opcode 7, Halt
void hlt();
//Opcode 8, Map segment
void map_segi(Mem_T m, uint32_t *regs, uint32_t rB, uint32_t rC);
//Opcode 9, Unmap segment
void unmap_segi(Mem_T m, uint32_t *regs, uint32_t rC);
//Opcode 10, Output
void output(uint32_t *regs, uint32_t rC);
//Opcode 11, Input
void input(uint32_t *regs, uint32_t rC);
//Opcode 12, Load Program
void load_prog(Mem_T m, uint32_t *regs, uint32_t rB);
//Opcode 13, Load Value
void load_val(uint32_t *regs, uint32_t rC, uint32_t val);