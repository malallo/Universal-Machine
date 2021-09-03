#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "assert.h"
#include "seq.h"
#include "mem-infra.h"

//Private function, creates new segment
seg new_seg(uint32_t len);

seg new_seg(uint32_t len)
{
    seg out = malloc(sizeof(struct seg));       //Make the segment
    out->len = len;                             //Set the length
    out->words = calloc(len, sizeof(uint32_t)); //Create the array of words
    return out;
}

//New segmented memory structure, gives pointer to where the mem is
Mem_T new_mem()
{
    Mem_T m = malloc(sizeof(struct Mem_T)); //We need to allocate the space first

    //Build the sequences
    Seq_T map = Seq_new(1);
    Seq_T unmap = Seq_new(1);

    //Set both sections
    m->mapped_segs = map;
    m->unmapped_segID = unmap;

    return m;
}
//Free segmented memory structure
void free_mem(Mem_T m)
{

    int map_seq_len = (int)Seq_length(m->mapped_segs);
    //Free mapped Segments
    for (int i = 0; i < map_seq_len; i++)
    {
        seg s = Seq_get(m->mapped_segs, i);
        if (s)
        {
            free(s->words);
            free(s);
        }
    }

    //Free unmapped segments
    map_seq_len = (int)Seq_length(m->unmapped_segID);

    for (int i = 0; i < map_seq_len; i++)
    {
        seg s = Seq_get(m->unmapped_segID, i);
        if (s)
        {
            free(s->words);
            free(s);
        }
    }

    //Free sequences
    Seq_free(&(m->mapped_segs));
    Seq_free(&(m->unmapped_segID));
    //Free the rest
    free(m);
}

//Make a new segment in memory with desired length
//Returns the segment id of newly created segment
uint32_t map_seg(Mem_T m, uint32_t len)
{
    //initialize what we're returning
    uint32_t seg_id = 0;

    //Build the segment
    seg s = new_seg(len);

    //Check for not mapped ids
    int len_id = Seq_length(m->unmapped_segID);
    if (len_id != 0)
    {
        seg_id = (uint32_t)(uintptr_t)Seq_remhi(m->unmapped_segID);
        Seq_put(m->mapped_segs, seg_id, s);
    }
    else
    {
        seg_id = Seq_length(m->mapped_segs);
        Seq_addhi(m->mapped_segs, s);
    }
    return seg_id;
}
//Unmap a segment using its segment ID and offset
void unmap_seg(Mem_T m, uint32_t seg_id)
{
    //Get segment from id
    seg to_clear = Seq_get(m->mapped_segs, seg_id);

    //Free segment and the words
    free(to_clear->words);
    free(to_clear);

    //NULL the mapped id
    Seq_put(m->mapped_segs, seg_id, NULL);

    //Add id to unmapped segment seq
    Seq_addhi(m->unmapped_segID, (void *)(uintptr_t)seg_id);
}

//Copy a segment's contents
void cpy_mem(Mem_T m, uint32_t seg_id)
{
    //copying and replacing 0 with itself is asinine, so we just return
    if (!seg_id)
    {
        return;
    }

    //Assume you can only copy mapped segments with seg ids greater than 0
    seg s = Seq_get(m->mapped_segs, seg_id);

    int len_seg = s->len;

    seg cpy_s = new_seg(s->len);
    //this is where the segment actually gets copied
    for (int i = 0; i < len_seg; i++)
    {
        cpy_s->words[i] = s->words[i];
    }

    seg zero = Seq_get(m->mapped_segs, 0);
    //Free and replace at 0
    free(zero->words);
    free(zero);

    Seq_put(m->mapped_segs, 0, cpy_s);
}
//Load a value from a segment given a segment ID and offset
uint32_t load_mem(Mem_T m, uint32_t seg_id, uint32_t offset)
{
    //get segment, then return the offset value
    seg s = Seq_get(m->mapped_segs, seg_id);
    return s->words[offset];
}
//Store a value into a segment given the segment ID and offset
void store_mem(Mem_T m, uint32_t seg_id, uint32_t offset, uint32_t val)
{
    //get segment, then assign value at offset
    seg s = Seq_get(m->mapped_segs, seg_id);
    s->words[offset] = val;
}