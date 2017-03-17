#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "msgs.h"

#define SOURCE_PORT  99


int client_port  = 0;

void server()
{
  
  char msg[10];
  int reply_port;

  // while(1){
    recv(SOURCE_PORT,msg);
    // Reply to be sent at port msg[0] 
    reply_port = (msg[0]-'0')*10 + (msg[1]-'0');
    printf("Server Receiving message at : %d  \n",SOURCE_PORT);
    printf("Message received by server : ");
    int i;
    for(i = 0;i < 10;i++){
      printf("%d  ",msg[i]);
    }
    printf("\n\n");

    strcpy(msg, "The file open has been received.")
    printf("Server Sending data to port %d \n\n",reply_port);
    send(reply_port,msg);
  // }

}

void client()
{
  
  char send_msg[10];
  char recv_msg[10];
  int reply_port;
  while(1){
  
  if(client_port == SOURCE_PORT-1){
    client_port = 0;
  }
  reply_port = client_port++;

  for(int i = 1; i< 10 ;i++){
    send_msg[i] = reply_port + i;
  }
  send_msg[0] = reply_port/100 +'0';
  send_msg[1] = reply_port%100 + '0';
  send_msg[2] = 'o';
  strcat(send_msg, "test1");
  send(SOURCE_PORT,send_msg);
  printf("Client Sent message with reply_port : %d \n\n", reply_port);

  recv(reply_port,recv_msg);
  printf("Client  Recv msg from port  : %d  \n", reply_port);
  printf("Message received by client %s: ", recv_msg);
  // for(int i = 1; i < 10 ; i++){
  //   printf("%d ",recv_msg[i]);
  // }
  printf("\n\n");

}

int main(int argc,char** argv)
{
  
  ReadyQueue = newQueue();
  initPort();

  start_thread(server);
  start_thread(client);
  
  run();

}