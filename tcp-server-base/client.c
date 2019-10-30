#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#define SA struct sockaddr
#define PORT 8080

int main(){
	int fd;
	char localhost[] = "127.0.0.1";

	// First we need to create a socket to communicate with the server
	fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd < 0){
		return -1;
	}	

	struct sockaddr_in sock_c;

	sock_c.sin_family = AF_INET;
	sock_c.sin_port = htons(PORT);
	sock_c.sin_addr.s_addr = inet_addr(localhost);

	int con;

	con = connect(fd, (SA*)&sock_c, sizeof(sock_c));
	if (con < 0){
		printf("Error while connecting\n");
		return -1;
	}

	printf("Connected successfully!\n");
}
