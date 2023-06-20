static stack_ty min = StackCrreate(element_size, capacity);
void StackMinPush(stack_ty* stack, void* value)
{
	if *(int*)value < *(int*)StackPeek(min)
	{
		StackPush(min, value);
	}
	StackPush(stack, value);
}

void StackMinPop(stack_ty* stack)
{
	if (StackPeek(stack) == StackPeek(min))
	{
		StackPop(min);
	}
	StackPop(stack);
}

void *GetMin()
{
	StackPeek(min);
}
