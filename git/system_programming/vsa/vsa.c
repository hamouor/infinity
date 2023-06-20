#include <assert.h>     /*assert*/

#include"vsa.h"

enum sizes{occ = 1, chunk_size = 31};
enum bool{False = 0, True = 1};

struct vsa
{
    unsigned int is_occupied: occ;
    unsigned int my_size: chunk_size;
    unsigned int back_neighbour_free_size: chunk_size;
    unsigned int is_last : occ;

};

static vsa_ty *NextHeader(vsa_ty* head);

static void UpdateHeader(vsa_ty *vsa, unsigned int occ, unsigned int size, unsigned int prevsize, unsigned int last);

vsa_ty *VSAInit(void *mem, size_t memory_size)
{
/*make sure memory_size is enough fot at least a vsa_ty + head*/
    vsa_ty* new_vsa = NULL;

    assert(mem && memory_size);

/*create and fill vsa handler at the beginning of mem */

/*at end of vsa handler create vsa_ty. occ = 0, my size = memory size - head - vsa. prev size = 0*/
    new_vsa = (vsa_ty*)mem;
    UpdateHeader(new_vsa, False, memory_size - sizeof(vsa_ty), 0, True);

/*return created vsa handler*/
    return new_vsa;
}

void *VSAAlloc(vsa_ty *vsa, size_t chunk_size)
{
    void* retval = NULL;
    size_t is_last = 0, new_size = 0;
    vsa_ty* curr_header = NULL, *next_header = NULL;

    assert(vsa);
    
    curr_header = vsa;

    while(!is_last)
    {
/*from vsa + 1 to vsa->total size. find header that says: free, size is enough. save pointer to beginning of block*/
        if (curr_header->is_occupied == False && curr_header->my_size >= chunk_size)
        {
            curr_header->is_occupied = True;
            retval = (void*)(curr_header + 1);
/*if all block is allocated just update header to show occupied +  update the next header->back_neighbour_free_size to 0*/
            if(curr_header->my_size - chunk_size <= sizeof(vsa_ty))
            {
                if (!curr_header->is_last)
                {
                    next_header = NextHeader(curr_header);
                    next_header->back_neighbour_free_size = 0;
                }
            }
/*if not all block is aloocd create at the end of allocation another header to show values and next header to..*/
            else
            {
                new_size = curr_header->my_size - chunk_size - sizeof(vsa_ty);
                is_last = curr_header->is_last;
                UpdateHeader(curr_header, curr_header->is_occupied, chunk_size, curr_header->back_neighbour_free_size, False);
                curr_header = NextHeader(curr_header);
                UpdateHeader(curr_header, False, new_size, 0, is_last);


                if (!curr_header->is_last) 
                {
                    next_header = NextHeader(curr_header);
                    next_header->back_neighbour_free_size = curr_header->my_size;
                }
            }
            is_last = 1;
        }
        else if (!curr_header->is_last)
        {
            curr_header = NextHeader(curr_header);
        }
        else
        {
            is_last = 1;
        }
    }
/*return the saved pointer*/
    return retval;
}

void VSAFree(void *chunk)
{
    vsa_ty* curr_header = NULL, *next_header = NULL, *prev_header = NULL;

    assert(chunk);

/*approach header and update value to be free. front neighbour is free, destroy header and add total size to my size*/
    curr_header = (vsa_ty*)((char*)chunk - sizeof(vsa_ty));
    curr_header->is_occupied = 0;
    if(!curr_header->is_last)
    {
        next_header = NextHeader(curr_header);
        if(!next_header->is_occupied)
        {
            UpdateHeader(curr_header, curr_header->is_occupied, curr_header->my_size + next_header->my_size + sizeof(vsa_ty), curr_header->back_neighbour_free_size, next_header->is_last);
        }
    }
/*if back neighbour free is > 0 approach their header and add total size to free*/
    if(curr_header->back_neighbour_free_size > 0)
    {
        prev_header = (vsa_ty*)((char*)curr_header - curr_header->back_neighbour_free_size - sizeof(vsa_ty));
        UpdateHeader(prev_header,prev_header->is_occupied, prev_header->my_size + curr_header->my_size + sizeof(vsa_ty), curr_header->back_neighbour_free_size, curr_header->is_last);
        curr_header = prev_header;
    }
    if(!curr_header->is_last)
    {
        next_header = NextHeader(curr_header);
        next_header->back_neighbour_free_size = curr_header->my_size;
    }
}

size_t VSALargestAvailable(vsa_ty *vsa)
{
    vsa_ty* curr_header = NULL;
    size_t largest = 0, is_last = 0;

    assert(vsa);

    curr_header = (vsa_ty*)vsa;
    while(!is_last)
    {
        if(curr_header->my_size > largest && !curr_header->is_occupied)
        {
            largest = curr_header->my_size;
        }
        if(!curr_header->is_last)
        {
            curr_header = NextHeader(curr_header);
        }
        else
        {
            is_last = 1;
        }
    }
    return largest;
}
/*go header to header and find largest free*/

static vsa_ty *NextHeader(vsa_ty* head)
{
    if(!head->is_last)
    {
        return ((vsa_ty*)((char*)(head + 1) + head->my_size));
    }
    return NULL;
}
static void UpdateHeader(vsa_ty *vsa, unsigned int occ, unsigned int size, unsigned int prevsize, unsigned int last)
{
    vsa->is_occupied = occ;
    vsa->my_size = size;
    vsa->back_neighbour_free_size = prevsize;
    vsa->is_last = last;
}

