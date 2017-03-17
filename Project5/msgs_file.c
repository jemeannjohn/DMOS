#include <stdio.h>   
#include <stdlib.h>   
#include <unistd.h>   
   
#include "msgs.h"   
   
#define SOURCE_PORT  99   
   
   
int client_port = 1; 
char fileNameList[100][100];
int portFileSize[100] = {0};  
   
void server()   
{     
  int msg[10];   
  int reply_port;  
  int requestCount = 0;  
  char port_map[100][22];  
  
  int i,j;  
  for(i=0;i<100;i++) {  
    for(j=0;j<22;j++) {  
      port_map[i][j] = '\0';  
    }  
  }  
  
  while(1) {  
  
    recv(SOURCE_PORT,msg);   
    // Reply to be sent at port msg[0]    
    reply_port = msg[0];  
    printf("Server Receiving message at : %d with opcode : %d  \n",SOURCE_PORT, msg[1]);   
    printf("Message received by server : ");   
    for(i = 0;i < 10;i++){   
      printf("%d",msg[i]);   
    }   
    printf("\n\n");   
  
    //Create file with .server extension  
    if(msg[1] == 0) {  
       
      if(requestCount >= 3) { 
        msg[0] = 'N'; 
        msg[1] = '_'; 
        msg[2] = 'O';  
        msg[3] = 'K';  
        msg[4] = '\0'; 
        printf("Server Sending data to port %d \n\n",reply_port);  
        send(reply_port,msg);  
 
      } else { 
        requestCount++; 
        printf("In Create-----\n");  
        char fileName[22];  
    for(i=0;i<22;i++) fileName[i]='\0'; 
        j=0;  
        int flag = 0, flag1=0; 
        for(i=2;i<10;i++){  
          if(msg[i] == -1) break;  
          // fileName[j++] = msg[i];  
          int m; 
      printf("%d\n",msg[i]); 
          char *p = (char*)&msg[i]; 
          for(m=0;m<4;m++) { 
             char c = *(p++);
         if(j>15 && c != -1) { flag = 1; break;} 
             fileName[j] = c;
          
         if(fileName[j] == -1) {  
        fileName[j] = '\0';  
        break; 
         } 
             j++; 
          }
        if(flag == 1) {flag1 = 1; break;} 
      printf("\n"); 
        } 
    if(flag1 ==1)
    {
        for(i=0;i<10;i++) {msg[i]='\0';} 
        msg[0] = '4';  
        msg[1] = '0';  
        msg[2] = '4'; 
        msg[3] = '\0'; 
        printf("Server Sending data to port %d \n\n",reply_port);  
        send(reply_port,msg)    ; 
}
else { 
        fileName[j++] = '.';  
        fileName[j++] = 's';  
        fileName[j++] = 'e';  
        fileName[j++] = 'r';  
        fileName[j++] = 'v';  
        fileName[j++] = 'e';  
        fileName[j++] = 'r';
        fileName[j] = '\0'; 
    
        printf("Creating file %s \n", fileName);  
        FILE *fp = fopen(fileName, "w");  
        fclose(fp);  
    printf("writing %s to port map at %d\n", fileName, reply_port); 
        strcpy(port_map[reply_port], fileName); 
    for(i=0;i<10;i++) {msg[i]='\0';} 
        msg[0] = 'O';  
        msg[1] = 'K';  
        msg[2] = '\0';  
        printf("Server Sending data to port %d \n\n",reply_port);  
        send(reply_port,msg); 
    } 
      } 
    } else if(msg[1] == 1){
        int sizeFlag = 0; 
        char fileName[22];  
    for(i=0;i<22;i++) fileName[i] = '\0'; 
        for(i=0;i<strlen(port_map[reply_port]);i++){  
    if (port_map[reply_port][i] == '\0') break;  
          fileName[i] = port_map[reply_port][i];  
        }  
     
        FILE *fp = fopen(fileName, "a");  
          
        for(i=2;i<10;i++) {  
          if(msg[i] != -1) { 
                if(portFileSize[reply_port] >= 1000000)
        {
                    sizeFlag = 1;
            break;
        }
        fputc(msg[i], fp); 
        portFileSize[reply_port]++;
          }  
            
        }  
        fclose(fp);
    for(i=0;i<10;i++) {msg[i]='\0';} 
    if(sizeFlag == 1) {
        msg[0] = '4';  
        msg[1] = '0';  
        msg[2] = '0';
        msg[3] = '\0';
            
    } else { 
        msg[0] = 'O';  
        msg[1] = 'K';  
        msg[2] = '\0'; 
    } 
        printf("Server Sending data to port %d \n\n",reply_port);  
        send(reply_port,msg);  
  
    } else if(msg[1] == 2) { 
      printf("In Close-----\n"); 
      requestCount--;
      for(i=0;i<10;i++) {msg[i]='\0';} 
      msg[0] = 'O';  
      msg[1] = 'K';  
      msg[2] = '\0';  
      printf("Server Sending data to port %d \n\n",reply_port);  
      send(reply_port,msg);  
 
    } 
  }  
}   
   
void client()   
{  
  char fileName[100]; 
  int index; 
  for(index =0;index<strlen(fileNameList[client_port-1]);index++){ 
    fileName[index] = fileNameList[client_port-1][index]; 
  } 
 
  int send_msg[10]; 
  int recv_msg[10];   
  int reply_port;
  
  if(client_port == SOURCE_PORT-1){   
    client_port = 1;   
  }  
  
  
  reply_port = client_port++;   
  int i;  
  for(i=0;i<10;i++) {  
    send_msg[i] = -1;  
  }  
  
  send_msg[0] = reply_port;  
  send_msg[1] = 0; 
 
  int msg_index=2, index_count=0; 
  i=0; 
  char fileNamePortion[5]; 
  int ll; 
  char *p = (char*)&(send_msg[msg_index]); 
 
  while(fileName[i] != '\0') {  
    if(index_count == 4) { 
      index_count = 0; 
      char *p = (char*)&(send_msg[msg_index++]); 
      for (ll=0 ; ll<4; ll++) 
      { 
        memset((void*)(p++), fileNamePortion[ll], 1); 
        fileNamePortion[ll] = '\0'; 
      } 
    }  
    fileNamePortion[index_count++] = fileName[i++]; 
  }  
 
  if(index_count != 0) { 
 
    char *p = (char*)&(send_msg[msg_index++]); 
    for(i=0;i<index_count;i++) { 
      memset((void*)(p++), fileNamePortion[i], 1); 
    } 
 
  } 
  while(1) {  
    printf("Message being sent to server at port %d :\n",SOURCE_PORT);  
    printf("The sent message is : ");  
    for(i=0;i<10;i++) { printf("%c ", send_msg[i]);}  
    printf("\n\n");  
    send(SOURCE_PORT,send_msg); 
    recv(reply_port,recv_msg); 
 
    for(i=0;i<10;i++){ 
      printf("%c", recv_msg[i]); 
    } 
    printf("\n\n"); 
  
    char status[10];  
    for(i=0;i<10;i++) {  
      if(recv_msg[i] !=-1){  
        status[i] = recv_msg[i];  
      } else {  
        status[i]= '\0';  
        break;  
      }  
    }
    if(strcmp(status,"404") == 0) {
      printf("Server responded with 404 :FileName Greater than the permitted limit exiting transfer.Blocking Thread.\n");    
      while(1){
        yield(); 
      }
    }
   
  
    if(strcmp(status, "OK") != 0) {  
      printf("Waiting for file %s\n", fileName); 
      yield();   
    }  
    else {  
      break;  
    }  
  }  
  
    
  i = 0; 
  FILE * fp = fopen( fileName, "r" );  
  send_msg[0] = reply_port;  
  send_msg[1] = 1;  
  
  for(i=2;i<10;i++) {  
    send_msg[i] = -1;  
  }  
  
  int count = 2, c;  
  while ((c = fgetc(fp)) != EOF)  
  {     
    if(count < 10) {  
      send_msg[count++] = c;  
    }  
    else {  
      count=2;  
      printf("Message being sent to server at port %d :\n",SOURCE_PORT);  
      printf("The sent message is : ");  
      for(i=0;i<10;i++) { printf("%c ", send_msg[i]);}  
      printf("\n\n");  
      send(SOURCE_PORT,send_msg);   
  
      recv(reply_port,recv_msg);
      char statusString[] = {recv_msg[0], recv_msg[1], recv_msg[2], '\0'};
      if(strcmp(statusString, "400") == 0) {
        printf("Server responded with 400 : The file has size >1Mb . Blocking further writing\n");
        while(1){yield();}
      }   
  
      send_msg[0] = reply_port;  
      send_msg[1] = 1;  
       for(i=2;i<10;i++) {  
        send_msg[i] = -1;  
      }  
      send_msg[count++] = c;  
    }  
  }  
    
  
  printf("Message being sent to server at port %d :\n",SOURCE_PORT);  
  printf("The sent message is : ");  
  for(i=0;i<10;i++) { printf("%c ", send_msg[i]);}  
  printf("\n\n");  
  
  send(SOURCE_PORT,send_msg);   
  
  recv(reply_port,recv_msg);   
  printf("Client  Recv msg from port  : %d  \n", reply_port);  
  send_msg[1] = 2; 
  send_msg[2] = '\0'; 
     
  send(SOURCE_PORT,send_msg);   
  
  recv(reply_port,recv_msg);  
 
  fclose( fp );  
  
  while(1) {  yield();}  
   
}   
   
int main(int argc,char* argv[])   
{   
  ReadyQueue = newQueue();   
  initPort();
  start_thread(server); 
  int i,j; 
  for(i=2;i<argc;i++){ 
      printf("%s\n", argv[i]); 
      for(j=0;j<strlen(argv[i]);j++) { 
          fileNameList[i-2][j] = argv[i][j]; 
      }
      fileNameList[i-2][j] = '\0';
      start_thread(client); 
  }     
  run();  
} 
 
