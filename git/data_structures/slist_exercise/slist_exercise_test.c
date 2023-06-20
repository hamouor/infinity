#include<stddef.h>
#include<stdio.h>

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

node_t *Flip(node_t *head);

int HasLoop(const node_t *head);

node_t *FindIntersection(node_t *head_1, node_t *head_2);

int main()
{
	node_t node1, node2, node3, node4, node5, node6, node7, node8;
	int a = 1, b=2, c=3, d=4, e=5, f=6, g=7, h=8;
	node1.data = &a;
	node1.next = &node2;
	node2.data = &b;
	node2.next = &node3;
	node3.data = &c;
	node3.next = &node4;
	node4.data = &d;
	node4.next = NULL;
	node5.data = &e;
	node5.next = &node6;
	node6.data = &f;
	node6.next = &node7;
	node7.data = &g;
	node7.next = &node8;
	node8.data = &h;
	node8.next = &node3;
	
	/*node1 = *Flip(&node1);*/
	printf("%d\n", *(int*)node1.data);
	b = HasLoop(&node5);
	printf("%d\n", b);
	node1 = *FindIntersection(&node1, &node5);
	printf("%d\n", *(int*)node1.data);
	return 0;
}

/* Reverses the order of a given list. */
node_t *Flip(node_t *head)
{
	node_t* prev = NULL, *current = head, *next = head -> next;
	
	while(next != NULL)
	{
		current -> next = prev;
		prev = current;
		current = next;
		next = next -> next;
	}
	
	return current;
}


/* check if the list has any loops in it as in - 
the pointers arent leading from the head to the tail  */
int HasLoop(const node_t *head)
{
    node_t *one_step = (node_t *)head, *two_steps = (node_t *)(head -> next);

    assert(head);

    /* step with pointers in different steps and compare positions, they nust meet after n steps in case of a loop */
    while (NULL != two_steps)
    {
        /* if they reach NULL its not a looped list */
        if ( one_step == two_steps)
        {
            return 1;
        }
        one_step = (one_step -> next);
        if (NULL != (two_steps -> next))
        {
            two_steps = ((two_steps -> next) -> next);
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

/* to find if two lists drain into a joined node */
node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	node_t *iter_1 = NULL, *iter_2 = NULL;
	
    assert(head_1);
    assert(head_2);

	iter_1 = Flip(head_1);
	Flip(iter_1);
    iter_2 = head_2;

    if (iter_1 == Flip(head_2))
    {
        while (iter_1 != iter_2)
        {
            if (NULL == iter_1)
            {
                iter_1 = head_2;
            }
            if (NULL == iter_2)
            {
                iter_2 = head_1;
            }
            iter_1 = (iter_1 -> next);
            iter_2 = (iter_2 -> next);
        }
        return iter_1;
    }
    else
    {
        return NULL;
    }

}

