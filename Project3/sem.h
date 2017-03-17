#include "threads.h"

typedef struct semaphore {
     int count;
     TCB_t *sem_queue;
} semaphore;

semaphore* CreateSem(int i)
{   
    semaphore *sem=(semaphore *)malloc(sizeof(semaphore));
    sem->count = i;
    sem->sem_queue = newQueue();
    return sem;
}

// Decrement count and block if < 0
void P(semaphore *sem)
{   
    TCB_t *temp;
    sem->count--;
    if(sem->count<0) 
    {
        printf("Blocking on P(sem)\n");
        addQueue(&(sem->sem_queue), &Curr_Thread);
        TCB_t *Prev_Thread = Curr_Thread;
        Curr_Thread = delQueue(&ReadyQueue);
        swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
    }
}

//Increment count and unblock a process waiting on the semaphore
void V(semaphore *sem)
{
    TCB_t *temp;
    sem->count++;
    if(sem->count<=0)
    {
        printf("Unlocking on V(sem)\n");
        temp = delQueue(&(sem->sem_queue));
        addQueue(&ReadyQueue,&temp);
    }
    yield();
}

