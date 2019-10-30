#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
#define SA struct sockaddr

int main(){
	printf("Starting execution of the server...\n");
	int fd_s, accept_fd;
	char localhost[] = "127.0.0.1";

	// Create TCP socket
	int domain = AF_INET;
	int type = SOCK_STREAM; // For TCP. SOCK_DGRAM for UDP
	
	fd_s = socket(domain, type, 0); 	// 0 to say "Any protocol"
	if (fd_s < 0){ 
		return -1;
	}
	printf("File descriptor is: %d \n", fd_s);

	// Now let's bind it
	printf("Binding the socket to address %s:%d...\n", localhost, PORT);
	
	struct sockaddr_in socket_address;
	int bind_code;
	
	socket_address.sin_family = AF_INET;
	//socket_address.sin_addr.s_addr = htonl(INADDR_ANY); // This is used for servers, to listen to any interface
	socket_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	socket_address.sin_port = htons(PORT); 
	
	if (bind_code = bind(fd_s, (SA*)&socket_address, sizeof(socket_address)) != 0){
		printf("Returned bind code: %d", bind_code);
		return -1;
	}
	printf("Socket binded!\n");

	//Make the server listen to this socket
	int listening = listen(fd_s, 1500);
	
	if (listening < 0){
		return -1;
	}
	printf("Server listening...\n");
	
	// Wait for the connections to come in
	while (1){
		accept_fd = accept(fd_s, (SA*)&socket_address, 0);
		if (accept < 0){
			printf("Error while accepting the connection\n");
			return -1;
		}
		printf("Accepted!\n");

		/*
		/  In this block, the idea is to write/read to/from the incoming connection
		*/

		close(accept_fd);
	}	
}
