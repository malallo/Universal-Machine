#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "bitpack.h" //Relies on provided bitpack now
#include "instrs.h"

//Define opcodes for ease of use
typedef enum
{
    COND_MOV,
    SEG_LD,
    SEG_ST,
    ADD,
    MUL,
    DIV,
    NAND,
    HLT,
    MAP,
    UNMAP,
    OUT,
    IN,
    LOAD_PROG,
    LOAD_VAL
} opcodes_t;

//Unpacks instructions using bitpack
uint32_t unbitpk_instr(Mem_T m, uint32_t *regs, uint32_t instr);