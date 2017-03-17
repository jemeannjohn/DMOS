#include "q.h"

TCB_t *RunQ; //Pointer to the Queue
ucontext_t parent;
void init() 
{
	RunQ = InitQ(RunQ);
}

void start_thread(void (*function)(void)) 
{
	int stack_size = 8192;
	void *stackP = malloc(stack_size);
	TCB_t *tcb = (TCB_t*)malloc(sizeof(struct tcb_t));
	init_TCB(tcb, function, stackP, stack_size);
	RunQ = AddQ(RunQ, tcb);
}

void run()
{
    
    getcontext(&parent);
    TCB_t *firsttcb = RunQ;
    swapcontext(&parent, &(firsttcb->context));
}

void yield() 
{
	TCB_t *temp;
	TCB_t *runningcontext, *nextcontext;
	runningcontext = RunQ;
	RunQ = RotateQ(RunQ);
	nextcontext = RunQ;
	if(RunQ==NULL)
			swapcontext(&(runningcontext->context), &parent);
	else
	swapcontext(&(runningcontext->context), &(nextcontext->context));
	
	
}
