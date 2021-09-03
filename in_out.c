#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "assert.h"

#include "in_out.h"
//Recieve an 8 byte char to then convert to uint32_t
int32_t get_inpt()
{
    int32_t wrd = getc(stdin);
    if (wrd < 0 || wrd > 255 || wrd == EOF) //if not within bounds or end-of-file
    {
        wrd = 256; //wrd is considered invalid at 256
    }
    return wrd;
}

//Recieve unsigned 32 bit char and print to stdout
void set_outpt(uint32_t w)
{
    assert(w <= 255);

    putc(w, stdout);

    //    fprintf(stderr, "Output is not between 0-255");
}