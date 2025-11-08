#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DOMAINE AF_INET //IPv4
#define TYPE SOCK_STREAM //type of communication we want to use, in this case we are using TCP communication
#define PROTOCOL 0

struct sockaddr_in addr; 
int main(){
  int sockfd, status;
  char text[255];

  sockfd = socket(DOMAINE, TYPE, PROTOCOL);
  if(sockfd < 0){
    perror("error");
    return sockfd;
  }
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = DOMAINE;
  addr.sin_port = htons(12345);
  inet_aton("192.168.1.6", &addr.sin_addr);

  status = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));

  if(status){
    perror("connect");
    close(sockfd);
    return status;
  }
  //if connection succed send a message to the server

  sprintf(text, "Salam from the Client\n");
  send(sockfd, text, strlen(text), 0);

  status = recv(sockfd, text, sizeof(text), 0);

  if(status > 0){
    printf("%s\n", text);
  }
  close(sockfd);
  return 0;
}
