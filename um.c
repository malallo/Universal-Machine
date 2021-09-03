#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "assert.h"
#include "seq.h"
#include "bitpack.h"

#include "mem-infra.h"
#include "instrs.h"
#include "in_out.h"
#include "parse_instr.h"

int main(int argc, char *argv[])
{
    //Check number of arguments

    if (argc > 2)
    {
        fprintf(stderr, "Too many arguments!");
        exit(1);
    }
    else if (argc < 2)
    {
        fprintf(stderr, "Too few arguments!");
        exit(1);
    }

    //Open um file
    FILE *fp = fopen(argv[1], "r");

    if (!fp)
    {
        fprintf(stderr, "File not valid");
        exit(1);
    }

    //Find length of file
    fseek(fp, 0L, SEEK_END);
    long int byt_sz = ftell(fp); //File size in bytes
    long int f_sze = byt_sz / 4; //32 bit ints in the file

    fseek(fp, 0L, SEEK_SET); //Reset the file pointer to start reading file

    //Create mem structure
    Mem_T m = new_mem();
    map_seg(m, f_sze);

    //Get all instructions from file in segment 0
    uint32_t val = 0;
    for (long int i = 0; i < f_sze; i++)
    {
        val = Bitpack_newu(val, 8, 24, (uint64_t)fgetc(fp));
        val = Bitpack_newu(val, 8, 16, (uint64_t)fgetc(fp));
        val = Bitpack_newu(val, 8, 8, (uint64_t)fgetc(fp));
        val = Bitpack_newu(val, 8, 0, (uint64_t)fgetc(fp));

        store_mem(m, 0, i, val);
    }
    //CLose um file
    fclose(fp);

    //Program counter set to 0
    long int prog_count = 0;

    //Create 8 registers initialized to 0
    uint32_t regs[8] = {0};

    while (1)
    {
        //Initialize program counter at seg 0
        uint32_t instr = load_mem(m, 0, (uint32_t)prog_count);
        //Rest of program is apart from seg 0
        prog_count++;
        //Returns -1 after instruction is carried out
        int32_t num = (int32_t)unbitpk_instr(m, regs, instr);

        if (num != -1)
        {
            prog_count = num;
        }
    }

    //Destroy mem structure, even if no halt instruction
    free_mem(m);
    return 0;
}