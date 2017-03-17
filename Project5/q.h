#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"

TCB_t* newItem() {
	TCB_t *newNode = (TCB_t*) malloc (sizeof(TCB_t));
	newNode->previous = NULL;
	newNode->next = NULL;
	newNode->threadId = 0;
	ucontext_t *ucon = &(newNode->context);
	ucon = NULL;
	return newNode;
}

TCB_t* newQueue()
{	
	TCB_t *dummy;
	dummy = newItem();
	dummy->previous = dummy;
	dummy->next = dummy;
	dummy->threadId = -1;
	return dummy;
}

void printQ(TCB_t *head) {
	TCB_t *temp; 
	temp = head;
	while(head->next != temp && head->next->threadId != -1) {
		printf("prev %d node %d next %d\n", head->previous->threadId,head->threadId,head->next->threadId);
		head = (head->next);
	}
	printf("prev %d node %d next %d\n\n", head->previous->threadId,head->threadId,head->next->threadId);

}

void addQueue(TCB_t** Q, TCB_t** temp)
{
    if((*Q)->next == *Q) {
        (*Q)->next = *temp;
    	(*temp)->previous = *Q;
	}
    else
    {		
    	(*Q)->previous->next = *temp;
    	(*temp)->previous = (*Q)->previous;
    }
    (*Q)->previous = *temp;
    (*temp)->next = *Q;
}


TCB_t* delQueue(TCB_t **Q)	{

	TCB_t *delNode;

	if((*Q)->next == *Q) {
		printf("Run queue is Empty, no TCB present.\n");
	}
	else {			
		delNode = (*Q)->next;
		if(delNode->next == *Q) {
			(*Q)->next = *Q;
           	(*Q)->previous = *Q;
		} else {
			(*Q)->next = delNode->next;
			delNode->next->previous = *Q;
		}
	}
	return delNode;
}
