#include <ucontext.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct tcb_t{
	ucontext_t context;
	struct tcb_t *llink;
	struct tcb_t *rlink;
}TCB_t;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    memset(tcb, '\0', sizeof(TCB_t));
    getcontext(&tcb->context);
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;	
    makecontext(&tcb->context, function, 0);
}
