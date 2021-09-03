#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "assert.h"
#include "mem-infra.h"
#include "in_out.h"
#include "instrs.h"

//Opcode 0, Conditional move
void cond_mov(uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC)
{
    if (regs[rC] != 0)
    {
        regs[rA] = regs[rB];
    }
}
//Opcode 1, Segmented Load
void seg_load(Mem_T m, uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC)
{
    regs[rA] = load_mem(m, regs[rB], regs[rC]);
}
//Opcode 2, Segmented Store
void seg_store(Mem_T m, uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC)
{
    store_mem(m, regs[rA], regs[rB], regs[rC]);
}
//Opcode 3, Addition
void add(uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC)
{
    //Adition cant go beyond 2^32
    regs[rA] = (uint32_t)(regs[rB] + regs[rC]);
}
//Opcode 4, Multiplication
void mult(uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC)
{
    //Multiplication cant go beyond 2^32
    regs[rA] = (uint32_t)(regs[rB] * regs[rC]);
}
//Opcode 5, Division
void div_i(uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC)
{
    //Can't check if regs[rC] is equal to zero without compilation error
    //if (regs[rC] != 0)
    //{
    regs[rA] = (uint32_t)(regs[rB] / regs[rC]);
    //Assume you cant divide by zero an you are restricted to numbers btwn 0-2^32
    //}
    //else
    //{
    //    fprintf(stderr, "Machine failed due to dividing by zero");
    //}
}
//Opcode 6, Bitwise NAND
void nand(uint32_t *regs, uint32_t rA, uint32_t rB, uint32_t rC)
{
    //Same 2^32 bit restriction here
    regs[rA] = ~(regs[rB] & regs[rC]);
}
//Opcode 7, Halt
void hlt()
{
    exit(0);
}
//For mapping and unmapping, a program can't map/unmap segment 0
//Opcode 8, Map segment
void map_segi(Mem_T m, uint32_t *regs, uint32_t rB, uint32_t rC)
{
    regs[rB] = map_seg(m, regs[rC]);
}
//Opcode 9, Unmap segment
void unmap_segi(Mem_T m, uint32_t *regs, uint32_t rC)
{
    unmap_seg(m, regs[rC]);
}
//Opcode 10, Output
void output(uint32_t *regs, uint32_t rC)
{
    set_outpt(regs[rC]);
}
//Opcode 11, Input
void input(uint32_t *regs, uint32_t rC)
{
    uint32_t hold_input = get_inpt();
    uint32_t end_bit = -1; //This is 0xffffff for 32 bits
    //See in_out where we determined that the end is defined with 256
    regs[rC] = (hold_input == 256) ? end_bit : hold_input;
}
//Opcode 12, Load Program
void load_prog(Mem_T m, uint32_t *regs, uint32_t rB)
{
    //See mem-infra interface
    cpy_mem(m, regs[rB]);
}
//Opcode 13, Load Value
void load_val(uint32_t *regs, uint32_t rC, uint32_t val)
{
    //Place value in regs[rC]
    regs[rC] = val;
}
