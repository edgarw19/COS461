#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 4096

int main(int argc, char *argv[]){
  FILE *messageFile;
  int status;
  struct addrinfo hints;
  struct addrinfo *results, *index;
  int s;
  char c[2];
  messageFile = fopen("message.txt", "r");

  if (messageFile == NULL) {
    printf("Invalid file");
    return 1;
  }
  if (argc != 2){
    fprintf(stderr, "usage: showip hostname\n");
    return 1;
  }
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  char buf[100];
  
  if ((status = getaddrinfo(argv[1], NULL, &hints, &results) != 0)){
    fprintf(stderr, "getaddrinfo error");
    return 1;
  }
  
  s = socket(index->ai_family, index->ai_socktype, index->ai_protocol);
  if (s == -1) {
    perror("client: socket");
	  return 1;
	}
  
  if (connect(s, index->ai_addr, index->ai_addrlen) == -1){
    close(s);
    perror("client: connect");
    return 1;
  }
  int len;
  while (fread(c, sizeof(char), 1, messageFile) == 1){
    c[1] = '\0';
    len = strlen(c)+1;
    send(s, c, len, 0);
  }
  freeaddrinfo(results);
  close(s);
  return 0;
}
