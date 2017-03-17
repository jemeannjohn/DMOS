#include"TCB.h"

TCB_t *getnode()
{
	TCB_t *x;
	x = (TCB_t*)malloc(sizeof(struct tcb_t));
	if(x==NULL) exit (0);
	x->rlink = x;
	x->llink = x;
	return x;
}

TCB_t *InitQ(TCB_t *Q) 
{
	Q = NULL;
	return Q;
}

// Add to the last element in the Queue
TCB_t *AddQ(TCB_t *Q, TCB_t *item) 
{
	TCB_t *temp = NULL, *curr = NULL;
	if(Q == NULL) 
	{
		item->llink = item;
		item->rlink = item;
		return item;
	}
	// Address of last element
	curr = Q->llink;
	// Insert at the end of the Queue
	Q->llink = item;
	item->rlink = NULL;
	item->llink = curr;
	curr->rlink = item;
	return Q;
}

// Delete the first element in the Queue and return the next element as the first element of the queue.
TCB_t *DelQ(TCB_t *Q) 
{
	TCB_t *prev, *next;
	// Queue is empty
	if(Q == NULL) return;

	next = Q->rlink;
	prev = Q->llink;
	prev->rlink = next;
	next->llink = prev;
	return next;
}

// Delete the first element and adds it to the tail, by just moving the header pointer to the next item.
TCB_t *RotateQ(TCB_t *Q)
{
	TCB_t *next;
	if(Q == NULL) return;

	next = Q->rlink;
	return next;	
}

