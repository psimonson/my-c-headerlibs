/*****************************************************
 * test2.c - Simplest server example, just prints a  *
 *           message to the client then quits.       *
 *****************************************************
 * Create by Philip "5n4k3" Simonson                 *
 *****************************************************
 */

#include "../common/sock_help.h"

#define PORT 5000

int main()
{
#ifdef _WIN32
	SOCKET sockfd, newfd;
#else
	int sockfd, newfd;
#endif
	struct sockaddr_in addr;
	int addrlen;
	
	/* create the listening server */
	sockfd = create_server(0, PORT, "0.0.0.0");
	if (sockfd == BAD_SOCKET)
		return 1;

	/* accepts client connection */
#ifdef _WIN32
	newfd = accept(sockfd, (struct sockaddr*)&addr,
			&addrlen);
#else
	newfd = accept(sockfd, (struct sockaddr*)&addr,
			(unsigned int*)&addrlen);
#endif
	if (newfd == BAD_SOCKET) {
		perror("accept");
		return 1;
	}
	
	send_msg(newfd, "Hello world, from a tcp/ip server.\r\n");
	close_conn(newfd);
	close_conn(sockfd);
	return 0;
}
