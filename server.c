#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define MAX_BUF 10
int main(int argc, char *argv[]){
  int sockfd, numbytes;
  char buf[MAX_BUF];
  struct addrinfo hints, *results, *index;
  struct sockaddr_storage sockAddrAccept;
  int status;
  socklen_t addrlen;
  if (argc != 2){
    fprintf(stderr, "usage: port name\n");
    exit(1);
  }
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if ((status=getaddrinfo(NULL, argv[1], &hints, &results)) != 0){
    fprintf(stderr, "getaddrinfo error\n");
  }
  for (index = results; index != NULL; index = index->ai_next){
    if ((sockfd = socket(index->ai_family, index->ai_socktype,
			 index->ai_protocol)) == -1){
      fprintf(stderr, "no client socket connections");
      continue;
    }
    if (bind(sockfd, index->ai_addr, index->ai_addrlen) == -1){
      close(sockfd);
      fprintf(stderr, "binding not successful");
      continue;
    }
    break;

  }
  if (index == NULL){
    fprintf(stderr, "listener: failed to bind socket\n");
    return 2;
  }
  listen(sockfd, 2);
   socklen_t addr_size = sizeof(sockAddrAccept);
  int new_fd;
  while(1){
    if ((new_fd = accept(sockfd, (struct sockaddr*)&sockAddrAccept, &addr_size)) < 0){
      fprintf(stderr, "Didn't accept");
      return 1;
    }
    //    if (!fork()){
    //close(sockfd);
      while (addr_size = recv(new_fd, buf, sizeof(buf), 0)){
	fwrite(buf, 1, sizeof(buf), stdout);
      }
      //exit(0);
      //}
    close(new_fd);
    
  }
  return 0;
  
}
