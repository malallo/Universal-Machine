#ifndef MEM_INFRA
#define MEM_INFRA

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "assert.h"
#include "seq.h"

typedef struct Mem_T
{
    Seq_T mapped_segs, unmapped_segID;
} * Mem_T;

typedef struct seg
{
    uint32_t *words;
    uint32_t len;
} * seg;

//New segmented memory structure, gives pointer to where the mem is
Mem_T new_mem();
//Free segmented memory structure
void free_mem(Mem_T m);

//Make a new segment in memory with desired length, gives id of newly created segment
uint32_t map_seg(Mem_T m, uint32_t len);
//Unmap a segment using its segment ID and offset
void unmap_seg(Mem_T m, uint32_t seg_id);

//Copy a segment's contents
void cpy_mem(Mem_T m, uint32_t seg_id);
//Load a value from a segment given a segment ID and offset
uint32_t load_mem(Mem_T m, uint32_t seg_id, uint32_t offset);
//Store a value into a segment given the segment ID and offset
void store_mem(Mem_T m, uint32_t seg_id, uint32_t offset, uint32_t val);

#endif