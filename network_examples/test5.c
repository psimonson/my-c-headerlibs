#include "../common/sock_help.h"

int main(int argc, char *argv[])
{
	CLIENT_INFO;
	char msg[256];
	char address[INET6_ADDRSTRLEN];
	int port, bytes;

	if (argc != 1 && argc != 3) {
		printf("Usage: %s <address> <port>\n", argv[0]);
		return 2;
	}
	if (argc == 3)
		sockfd = create_client(0, atoi(argv[2]), argv[1]);
	else
		sockfd = create_client(0, 5000, "127.0.0.1");
	if (sockfd == BAD_SOCKET)
		return 1;

	/* do something with server */
	get_addr_info(sockfd, address, &port);
	sprintf(msg, "Connected to %s on port %d.", address, port);
	puts(msg);

	memset(msg, 0, sizeof msg);
	/* recv message from server */
	while ((bytes = recv(sockfd, msg, sizeof msg, 0)) > 0) {
		printf("%s", msg);
		memset(msg, 0, sizeof msg);
	}
	memset(msg, 0, sizeof msg);
	if (bytes == 0)
		printf("Disconnected from %s\n", address);
	else
		printf("Error receiving from %s\n", address);
	close_conn(sockfd);
	return 0;
}
