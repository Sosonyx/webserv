#include <unistd.h>
#include <poll.h>
#include <cstdio>
#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>

int main(int ac, char **av)
{
	(void)ac, (void)av;
	int clientSocket[10];
	while(1)
	{
		int i = 0;
		// pollfd fds;
		// poll(fds, );
		int socketFd = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = INADDR_ANY;
		serverAddress.sin_port = htons(8080);
		bind(socketFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
		listen(socketFd, 1024);
		clientSocket[i] = accept(socketFd, 0, 0);
		fcntl(clientSocket[i], O_NONBLOCK);
		char buffer[2000] = {0};
		recv(clientSocket[i], buffer, sizeof(buffer), 0);
		// buffer[size] = 0;
		std::cout << buffer << "\n";
		close(socketFd);
		i++;
	}

}	