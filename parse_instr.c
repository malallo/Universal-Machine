#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "bitpack.h" //Relies on provided bitpack now
#include "instrs.h"
#include "parse_instr.h"

/* 
From parse_instr.h:
    Define opcodes for ease of use
    typedef enum { COND_MOV, SEG_LD, SEG_ST,
        ADD, MUL, DIV, NAND, HLT, MAP, UNMAP, OUT, IN, 
        LOAD_PROG, LOAD_VAL} opcodes_t;

*/

//Define Opcode size in bits & least significant bit
uint32_t const OPC_SZ = 4, OPC_LSB = 28;
//Define register size in bits
uint32_t const REG_SZ = 3;
//Define value size needed for opcode 13, LOAD_VAL
uint32_t const VAL_SZ = 25;

//Unpacks instructions using bitpack
uint32_t unbitpk_instr(Mem_T m, uint32_t *regs, uint32_t instr)
{

    //Get opcode using bitpack
    uint32_t opcd = Bitpack_getu(instr, OPC_SZ, OPC_LSB);

    //Sets up each code in numerical order. Based on the code, set up the variables and call the function
    if (opcd == COND_MOV) //Opcode 0, Conditional move
    {
        uint32_t rA = Bitpack_getu(instr, REG_SZ, 6);
        uint32_t rB = Bitpack_getu(instr, REG_SZ, 3);
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        cond_mov(regs, rA, rB, rC);
    }

    else if (opcd == SEG_LD) //Opcode 1, Segmented Load
    {
        uint32_t rA = Bitpack_getu(instr, REG_SZ, 6);
        uint32_t rB = Bitpack_getu(instr, REG_SZ, 3);
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        seg_load(m, regs, rA, rB, rC);
    }

    else if (opcd == SEG_ST) //Opcode 2, Segmented Store
    {
        uint32_t rA = Bitpack_getu(instr, REG_SZ, 6);
        uint32_t rB = Bitpack_getu(instr, REG_SZ, 3);
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        seg_store(m, regs, rA, rB, rC);
    }

    else if (opcd == ADD) //Opcode 3, Addition
    {
        //Addition must not be
        uint32_t rA = Bitpack_getu(instr, REG_SZ, 6);
        uint32_t rB = Bitpack_getu(instr, REG_SZ, 3);
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        add(regs, rA, rB, rC);
    }

    else if (opcd == MUL) //Opcode 4, Multiplication
    {
        uint32_t rA = Bitpack_getu(instr, REG_SZ, 6);
        uint32_t rB = Bitpack_getu(instr, REG_SZ, 3);
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        mult(regs, rA, rB, rC);
    }

    else if (opcd == DIV) //Opcode 5, Division
    {
        //Assume that no division by 0 is allowed
        uint32_t rA = Bitpack_getu(instr, REG_SZ, 6);
        uint32_t rB = Bitpack_getu(instr, REG_SZ, 3);
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        div_i(regs, rA, rB, rC);
    }

    else if (opcd == NAND) //Opcode 6, Bitwise NAND
    {
        uint32_t rA = Bitpack_getu(instr, REG_SZ, 6);
        uint32_t rB = Bitpack_getu(instr, REG_SZ, 3);
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        nand(regs, rA, rB, rC);
    }

    else if (opcd == HLT) //Opcode 7, Halt
    {
        hlt(); //exit(0)
    }

    else if (opcd == MAP) //Opcode 8, Map segment
    {
        uint32_t rB = Bitpack_getu(instr, REG_SZ, 3);
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        map_segi(m, regs, rB, rC);
    }

    else if (opcd == UNMAP) //Opcode 9, Unmap segment
    {
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        unmap_segi(m, regs, rC);
    }

    else if (opcd == OUT) //Opcode 10, Output
    {
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        output(regs, rC);
    }

    else if (opcd == IN) //Opcode 11, Input
    {
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        input(regs, rC);
    }

    else if (opcd == LOAD_PROG) //Opcode 12, Load Program
    {
        uint32_t rB = Bitpack_getu(instr, REG_SZ, 3);
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 0);
        load_prog(m, regs, rB);
        return regs[rC];
    }

    else if (opcd == LOAD_VAL) //Opcode 13, Load Value
    {
        uint32_t rC = Bitpack_getu(instr, REG_SZ, 25);
        uint32_t val = Bitpack_getu(instr, VAL_SZ, 0);
        load_val(regs, rC, val);
    }
    return -1;
}