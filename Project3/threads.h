#include "q.h"

TCB_t *ReadyQueue;
TCB_t *Curr_Thread;
static int count = 0; 

void start_thread(void *runFunction) 
{
  void *stackAlloc =  (void*)malloc (8192);
  TCB_t *tcbAlloc = newItem();
  init_TCB(tcbAlloc, runFunction, stackAlloc, 8192);
  count++;
  tcbAlloc->threadId = count;
  addQueue(&ReadyQueue,&tcbAlloc);
}

void run()
{	
	Curr_Thread = delQueue(&ReadyQueue);
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
  swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}

void yield()
{ //get the previous thread context 
  TCB_t *Prev_Thread; 
	
  addQueue(&ReadyQueue, &Curr_Thread);
  Prev_Thread = Curr_Thread;
  Curr_Thread = delQueue(&ReadyQueue);
  swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));  // start the first thread
}
