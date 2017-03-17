#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "msgs.h"


#define SOURCE_PORT  99


int client_port  = 0;

void server()
{
  
  int msg1[10];
  int reply_port;

  while(1){
    recv(SOURCE_PORT,msg1);
    // Reply to be sent at port msg[0] 
    reply_port = msg1[0];
    printf("Server Receiving message at : %d  \n",SOURCE_PORT);
    printf("Message received by server : ");
    int i;
    for(i = 0;i < 10;i++){
      printf("%d  ",msg1[i]);
    }
    printf("\n\n");

    for(i = 0;i < 10;i++){
      msg1[i] = msg1[i]*2;
    }
    printf("Server Sending data to port %d \n\n",reply_port);
    send(reply_port,msg1);
  }

}

void client()
{
  
  int send_msg[10];
  int recv_msg[10];
  int reply_port;
  while(1){
  
  if(client_port == SOURCE_PORT-1){
    client_port = 0;
  }
  reply_port = client_port++;

  for(int i = 1; i< 10 ;i++){
    send_msg[i] = reply_port + i;
  }
  send_msg[0] = reply_port;
  send(SOURCE_PORT,send_msg);
  printf("Client Sent message with reply_port : %d \n\n", reply_port);

  recv(reply_port,recv_msg);
  printf("Client  Recv msg from port  : %d  \n", reply_port);
  printf("Message received by client : ");
  for(int i = 1; i < 10 ; i++){
    printf("%d ",recv_msg[i]);
  }
  printf("\n\n");
  }

}



// Main function //
int main(int argc,char** argv)
{
  
  ReadyQueue = newQueue();
  initPort();

  start_thread(server);
  start_thread(client);
  start_thread(client);
  start_thread(client);
  start_thread(client);
  start_thread(client);
  
  run();

}