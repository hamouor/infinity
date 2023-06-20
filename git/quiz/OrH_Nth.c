slist_node_ty *FindNth(slist_ty list, int N)
{
	return (slist_node_ty)FindNthRec(SlistBegin(list), SlistEnd(list), N);
}

void *FindNthRec(slist_node_ty *node, slist_node_ty *tail, int N)
{
	if( SlistIterIsEqual(node,tail) )
	{
		return (void*)0;
	}
	if ((1 + (int)FindNthRec(SlistNext(node), tail, N)) == N)
	{
		return (void*)node;
	}
	return NULL;
}

slist_node_ty *FindNthII(slist_ty list, int N)
{
	slist_node_ty* runner = SlistBegin(list), *end  = SlistEnd(list), *temp = NULL;
	int count = 0;
	
	while(!SlistIterIsEqual(runne, end))
	{
		runner = SlistNext(runner);
		if (N > count)
		{
			++count;
		}
		else if (!temp)
		{
			temp = SlistBegin(temp);
		}
		else
		{
			temp = SlistNext(temp);
		}
	}
	return temp;
}
