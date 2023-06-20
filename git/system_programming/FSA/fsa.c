#include <assert.h>

#include"fsa.h"

typedef struct headero
{
    struct headero* next_free;
}header;

struct fsa
{
    header* first_free;
};

enum sizes {wordsize = 8};

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
    /* calculate block_actual = (block_size / 8 + !!block_size % 8 + 1)*8*/
    size_t block_actual = 0, header_and_block = 0, retval = 0;

    header_and_block = block_size + sizeof(header);
    block_actual = ( ( header_and_block / wordsize ) + ( !!( header_and_block % wordsize ) ) ) * wordsize;
    retval = ( block_actual ) * num_of_blocks + sizeof(fsa_ty);

    /*return num_of_blocks * block_actual + sizeof(fsa)*/
    return retval;
}


fsa_ty *FSAInit(void *mem, size_t memory_size, size_t block_size)
{
    size_t block_actual = 0, header_and_block = 0, fsa_actual = 0, num_of_blocks = 0, i = 0;
    fsa_ty *new = NULL;
    header* block_header = NULL;
    char* start = NULL;

    assert(mem);
    
/*block_actual = (block_size / 8 + !!block_size % 8 + 1)*8*/
    header_and_block = block_size + sizeof(header);
    block_actual = ( ( header_and_block / wordsize ) + ( !!( header_and_block % wordsize ) ) ) * wordsize;
    fsa_actual = ( ( sizeof(fsa_ty) / wordsize ) + ( !!( sizeof(fsa_ty) % wordsize ) ) ) * wordsize;
/*(size - sizeof(fsa))/block_actual = num_of_blocks*/
    num_of_blocks = ( memory_size - fsa_actual ) / block_actual;
    
/*at first place of mem- fsa containing pointer to mem+8bytes*/
    new = mem;
    new->first_free = (header*)((char*)new + fsa_actual);
    start = (char*)(new->first_free);
    
/*for num_of_blocks-1  mem+8+i*block_actual has ptr to mem+8+(i+1)*block_actual*/
    for(; i < num_of_blocks - 1; ++i)
    {
        block_header = (header*)start;
        start = start + block_actual;
        block_header->next_free = (header*)(start);
    }
    block_header = (header*)start;
    block_header->next_free = NULL;

/*return fsa* to mem*/
    return new;
}

void *FSAAlloc(fsa_ty *fsa)
{
    void* retval = NULL;

    assert(fsa);

/*retval = fsa->next_free*/
    retval = (void*)(fsa->first_free);
    if(retval != NULL)
    {
        retval = (void*)((char*)retval + wordsize);
/*fsa->nextfree = fsa->next_free->next_free*/
        fsa->first_free = (fsa->first_free)->next_free;
    }
/*return retval*/
    return retval;
}

void FSAFree(fsa_ty *fsa, void *block)
{
    header* block_header = NULL;
    
    assert(block);

/*header of block points to fsa->next free*/
    block_header = (header*)((char*)block - wordsize);
    block_header->next_free = fsa->first_free;
/*fsa->next_free points to block*/
    fsa->first_free = block_header;
}

size_t FSACountFree(const fsa_ty *fsa)
{
    size_t count = 0;
    header* block_header = NULL;

    assert(fsa);

    block_header = fsa->first_free;
    while(block_header != NULL)
    {
        block_header = block_header->next_free;
        ++count;
    }

    return count;
}
/*from fsa first_free to header->next_free = NULL, count*/
/*return count*/

