/*   
Jeme John(1209042532),
Vivek Jadon(1209381703) 
*/


#include "sem.h"

typedef struct msg_Q{
		struct msg_Q* 	next;
		struct msg_Q* 	previous;
		int msg[10];
} msg_Q;

typedef struct port{
		msg_Q*		head;
		semaphore mutex, full, empty;
} port;

port ports[100];

msg_Q* newMsgItem() {
	msg_Q *newNode = (msg_Q*) malloc (sizeof(msg_Q));
	newNode->previous = NULL;
	newNode->next = NULL;
	for(int i=0;i<10;i++)
	{
		newNode->msg[i] = 0;
	}
	return newNode;
}

msg_Q* newMsgQueue()
{	
	msg_Q *dummy;
	dummy = newMsgItem();
	dummy->previous = dummy;
	dummy->next = dummy;
	return dummy;
}

void initPort() 
{
	for(int i=0;i<100;i++)
	{
		ports[i].head = newMsgQueue();
		ports[i].mutex = *(CreateSem(1));
		ports[i].full = *(CreateSem(10));
		ports[i].empty = *(CreateSem(0));
	}
}


void addMsgQueue(msg_Q** Q, int msg[10])
{
	msg_Q *temp;
	temp = newMsgItem();
	for(int i=0;i<10;i++) {
		temp->msg[i] = msg[i];
	}

    if((*Q)->next == *Q) {
        (*Q)->next = temp;
    	(temp)->previous = *Q;
	}
    else
    {		
    	(*Q)->previous->next = temp;
    	(temp)->previous = (*Q)->previous;
    }
    (*Q)->previous = temp;
    (temp)->next = *Q;
}



msg_Q* delMsgQueue(msg_Q **Q)	{

	msg_Q *delNode;

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

void send(int port_num, int msg[10])
{

	P(&ports[port_num].full);
	P(&ports[port_num].mutex);
	addMsgQueue(&ports[port_num].head,msg);
	V(&ports[port_num].mutex);
	V(&ports[port_num].empty);

}


void recv(int port_num, int* msg)
{
	
	msg_Q	*delNode;

	P(&ports[port_num].empty);
	P(&ports[port_num].mutex);
	delNode = delMsgQueue(&ports[port_num].head);
	V(&ports[port_num].mutex);
	V(&ports[port_num].full);

	for(int i = 0; i < 10;i++){
		msg[i] = delNode->msg[i];
	}

}



