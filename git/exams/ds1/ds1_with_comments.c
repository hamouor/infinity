/*  QUESTION 1 - ALLOC AND FREE FOR ALIGNED FSA */

void *FSAAlloc(fsa_ty *fsa)
{
    void* retval = NULL;

    assert(fsa);

/*retval = fsa->next_free*/								/* XXX: Fixing comments alignments and spacing might be nice */
    retval = (void*)(fsa->first_free);
    if(retval != NULL)
    {
        retval = (void*)((char*)retval + wordsize);		/* XXX: Good enough but maybe using your 'header size' rather than 'wordsize' will suit better */
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
    block_header = (header*)((char*)block - wordsize); /* XXX: same here */
    block_header->next_free = fsa->first_free;
/*fsa->next_free points to block*/
    fsa->first_free = block_header;
}

/*  QUESTION 1 - ALLOC AND FREE FOR ALIGNED VSA */	/* XXX: Didn't check it because we haven't finished that exerice yet */

void *VSAAlloc(vsa_ty *vsa, size_t chunk_size)
{
    void* retval = NULL;
    size_t is_last = 0, new_size = 0;
    vsa_ty* curr_header = NULL, *next_header = NULL;

    assert(vsa);
    
    /*alignment of chunk size*/
    chunk_size = ((chunk_size / wordsize) + (!(chunk_size % wordsize))) * wordsize;
    curr_header = vsa;

    while(!is_last)
    {
/*from vsa + 1 to vsa->total size. find header that says: free, size is enough. save pointer to beginning of block*/
        if (curr_header->is_occupied == 0 && curr_header->my_size >= chunk_size)
        {
            curr_header->is_occupied = 1;
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
                curr_header->my_size = chunk_size;
                is_last = curr_header->is_last;
                curr_header->is_last = 0;
                curr_header = NextHeader(curr_header);
                curr_header->is_occupied = 0;
                curr_header->my_size = new_size;
                curr_header->back_neighbour_free_size = 0;
                curr_header->is_last = is_last;

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
            curr_header->my_size += next_header->my_size + sizeof(vsa_ty);
            curr_header->is_last = next_header->is_last;
        }
    }
/*if back neighbour free is > 0 approach their header and add total size to free*/
    if(curr_header->back_neighbour_free_size > 0)
    {
        prev_header = (vsa_ty*)((char*)curr_header - curr_header->back_neighbour_free_size - sizeof(vsa_ty));
        prev_header->my_size += curr_header->my_size + sizeof(vsa_ty);
        prev_header->is_last = curr_header->is_last;
        curr_header = prev_header;
    }
    if(!curr_header->is_last)
    {
        next_header = NextHeader(curr_header);
        next_header->back_neighbour_free_size = curr_header->my_size;
    }
}

/*  QUESTION 2 - FLIP */

node *Flip(node *node)			/* XXX: Very nice short solution! I did it quite different */
{
    node *next = NULL;
    node *prev = NULL

    assert(node);

    while (NULL != next)		/* XXX: your loop will never get executed. Check your 'next' definition few rows above here */
    {
        next = node->next;
        node->next = prev;
        prev = node;
        node = next;
    }

    return prev;
}

/*  QUESTION 3 - SINGLY LINKED LIST COMPLEXITY OF OPERATIONS */

/*no random access, meaning any time we need to get to a specific node or iterate over list - O(n)*/
/*create - 1. destroy - n. */

/*  QUESTION 4 - HAS LOOP*/

node *HasLoop(node *start)
{
    node *buff = NULL;
    
    assert(start);

    buff = strat;
    start = Flip(start);			/* XXX: Nice reuse */
    if (buff == start)
    {
        start = Flip(start);
        return HAS_LOOP;			/* XXX: Your return doesn't match HasLoop return values. Also could've been nice if you included what are those macros */
    }
    else
    {
        start = Flip(start);
        return NO_LOOP;
    }
}


/*  QUESTION 4 - OPEN LOOP*/
/* XXX: Curious about the 2 funcs in comments below */
/*LoopNode - returns the node in which a loop was confirmed instead of int*/
/*FindIntersection - returns the node of intersection between two listst given two heads*/

node_t* OpenLoop(node_t* head)
{
    node_t* head2 = NULL, *temp = NULL, *temp2 = NULL;

    temp = LoopNode(head);
    head2 = temp->next;
    temp->next = NULL;

    temp2 = FindIntersection(head, head2);
    temp->next = head2;

    while(head2->next != temp2)
    {
        head2 = head2->next;
    }
    head2->next = NULL;
}

/*  QUESTION 5 - FIND INTERSECTION*/

int IsIntersection(node *head1, node *head2)	/* XXX: Very nice */
{
    assert(head1);
    assert(head2);

    head1 = Flip(head1);
    head2 = Flip(head2);

    /* if both has the same tail - tough luck */
    return head1 == head2 ? INTERSECTED : NOT_INTERSECTED;
}

void SeperateIntersected(node *head1, node *head2)
{
    node *intersection = NULL;

    assert(head1);
    assert(head2);

    intersection = FindIntersection(head1, head2);
    while (intersection != head1)
    {
        head1 = head1->next;
    }
    
    head1->next = NULL;
}

/*  QUESTION 6 - REMOVE*/

slist_iter_ty SlistRemove(slist_iter_ty iter)
{
	slist_node_ty *temp = NULL;
	
	assert(iter);
	
	temp = ITERTONODE(SlistNext(iter));
	if (temp == NULL)
	{
		return iter;
	}
	SlistSetData(iter, SlistGetData(SlistNext(iter)));;
	(ITERTONODE(iter))->next =SlistNext(SlistNext(iter));
	free(temp);
	
	return iter;
}

/* QUESTION 7 - INSERT AND REMOVE FOR DLIST*/

dlist_iter_ty DlistInsertBefore(dlist_iter_ty iter, const void *data)
{
	dlist_node_ty *iter_node = NULL;
	dlist_node_ty *new_node = NULL;
	
	assert(ITER2NODE(iter));
	
	new_node = (dlist_node_ty *)malloc(sizeof(dlist_node_ty));
	
	if (NULL == new_node)
	{
		return GetListTail(iter);
	}
	
	iter_node = ITER2NODE(iter);
	iter_node->prev->next = new_node;
	new_node->next = iter_node;
	new_node->prev = iter_node->prev;
	iter_node->prev = new_node;
	new_node->data = (void *)data;
	
	return NODE2ITER(new_node);
}

dlist_iter_ty DlistRemove(dlist_iter_ty iter)
{
	dlist_iter_ty result = NULL_ITER;
	dlist_node_ty *iter_node = NULL;
	
	iter_node = ITER2NODE(iter);
	
	assert(iter_node);
	
	iter_node->prev->next = iter_node->next;
	iter_node->next->prev = iter_node->prev;
	
	result = NODE2ITER(iter_node->next);
	
	free(iter_node);
	iter_node = NULL;
	
	return result;
}

/* QUESTION 8*/
/*SUM 0-1024. SUM ARRAY. SUM - SUM = MISSING NUMBER*/

/*QUESTION 9*/
/*SEND LINES IN ALL(?) DIRECTIONS, ALL LINES MUST MEET AN ODD NUMBER OF BOUNDERIES. SUM OF BITS ON THE LINE IS ODD*/

/*  QUESTION 10*/

int PushChar(struct QUEUE q, char ch)	/* XXX: you meant struct pointers I guess */
{
    if(q->m_elements_in_q < Q_SIZE)
    {
        int pos = 0;
        pos = (q->m_elements_in_q + q->m_first_element + 1) % Q_SIZE;
        q->m_queue[pos] = ch; 
        return 1;	/* XXX: floating numbers */
    }/* XXX: what about m_elements_in_q incrementation? */
    return 0;
}

char PopChar(struct QUEUE q) /* XXX: same here */
{
    char retval = '\0';

    retval = q->m_queue[q->m_first_element];
    q->m_elements_in_q -= 1;
    q->m_first_element = (q->m_first_element + 1) % Q_SIZE;

    return retval;
}
