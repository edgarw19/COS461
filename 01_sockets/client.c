#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[]){
	int status;
	struct addrinfo hints;
	struct addrinfo *results, *index;
	int s;

	if (argc != 2){
		fprintf(stderr, "usage: showip hostname\n");
		return 1;
	}
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo("www.cnn.com", "80", &hints, &results) != 0){
		fprintf(stderr, "getaddrinfo error");
	}
	for (index = results; index != NULL; index = index->ai_next){
		void *addr;
		char *ipver;
		s = socket(index->ai_family, index->ai_socktype, index->ai_protocol);
		connect(s, index->ai_addr, index->ai_addrlen);

	}
	freeaddrinfo(results);
	return 1;
}