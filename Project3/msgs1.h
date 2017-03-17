/*
 *  msgs.h
 */


#include "sem.h"

#define NUM_PORTS		100
#define PORT_CAP		10
#define MSG_SIZE		10

static int	init_flag = 0;

typedef struct msg_Q{
		struct msg_Q* 	next;
		struct msg_Q* 	previous;
		int msg[10];
}msg_Q;

typedef struct port{
		msg_Q*		head;
		semaphore  full, empty;
}port;

port ports[NUM_PORTS];
semaphore mutex;

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
	printf("\n\t\t\t\t\t\tInitialize Ports\n");
	printf("\t\t\t\t\t\t*******************\n");
	int i;
	mutex = *(CreateSem(1));
	for(i=0;i<100;i++)
	{
		ports[i].head = newMsgQueue();
		ports[i].full = *(CreateSem(0));
		ports[i].empty = *(CreateSem(10));
		
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




// Send function 
void send(int port_num, int msg[10])
{

	P(&ports[port_num].empty);
	P(&mutex);
	addMsgQueue(&ports[port_num].head,msg);
	V(&mutex);
	V(&ports[port_num].full);

}



// Recv function
void recv(int port_num, int* msg, int k, int l)
{
	msg_Q *new1;
	if(k ==0){
		printf("Receive on server loop: %d\n",l);
	} else printf("Receive on client loop: %d\n",l);

	P(&ports[port_num].full);
	P(&mutex);
	new1 = delMsgQueue(&ports[port_num].head);
	V(&mutex);
	V(&ports[port_num].empty);

	for(int i = 0; i < 10;i++){
		msg[i] = new1->msg[i];
	}

	if(new1){
		free(new1);
		new1 = NULL;
	}

}



