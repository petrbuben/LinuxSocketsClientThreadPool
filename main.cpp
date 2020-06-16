#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <pthread.h>

int main(){//client

  char message[2000];
  char buffer[2000];

  //memset(message,0,sizeof(message));
  //memset(buffer,0,sizeof(buffer));

  int clientSocket;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  int i;

  printf ("client\n");

  //more clients - doesn't work like this
  for(i=0;i<150;i++){

  //Create the socket.
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  if(clientSocket < 0){
     perror("client socket creation error");
     exit(-1);
  }

  //Configure settings of the server address
  //Address family is Internet
  serverAddr.sin_family = AF_INET;

  //Set port number, using htons function - must know about server
  serverAddr.sin_port = htons(7799);

  //Set IP address to localhost - must know about server
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  //Connect the socket to the server using the address
  addr_size = sizeof serverAddr;
  int c = connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  if (c <0){
    perror("from client: failed to connect, exiting\n");
    exit(-1);
  }

  //strcpy(message,"Hello from client");
  sprintf(message,"%s %d", "Hello from client", i );
  printf("\nconnected, sending to server.. \n");

  //send to server
  if( send(clientSocket , message , strlen(message) , 0) < 0)
  {
    printf("from client: Send failed\n");
    exit(-1);
  }

  //Read the message from the server into the buffer
  //if(recv(clientSocket, buffer, 2000, 0) < 0)
  //if(read(clientSocket, buffer, 2000) < 0)
  if(recv(clientSocket, buffer, 2000, 0) < 0)
  {
    printf("from client: Receive failed\n");
  }

  //Print the received message
  printf("Data received from server: %s\n", buffer);

  close(clientSocket);
 }//for

  return 0;

}
