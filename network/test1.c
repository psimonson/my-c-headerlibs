/**************************************************
 * Sample 1 - Using the networking library.       *
 **************************************************
 * Created by Philip R. Simonson (aka 5n4k3)      *
 **************************************************
 */

/* uncomment for windows build... */
/* #define WINDOWS */
#include "../common/sock_help.h"

#define MAXLINE		1024

/* program to handle multiple clients simple chat server */
int main(int argc, char *argv[])
{
	struct sockaddr_in addr;
	char line[MAXLINE];
	char message[MAXLINE];
	int serverfd;
	int addrlen;
	int newfd;

	/* create server socket */
	serverfd = create_server(0, 5555, "0.0.0.0");
	if (serverfd < 0)	/* handle error */
		return -1;
	addrlen = sizeof(addr);
	newfd = accept(serverfd, (struct sockaddr*)&addr,
		(unsigned int*)&addrlen);
	if (newfd < 0)
		perror("accept");
	puts("Client connected!");

	while (1) {
		int bytes;

		if ((bytes = getln_remote(newfd, line, sizeof(line))) <= 0) {
			if (bytes == 0) {
				puts("Client disconnected!");
			} else {
				perror("recv");
			}
			close_conn(newfd);
			break;
		} else {
			/* handle sending data */
			bytes = send_msg(newfd, "You gave me...\r\n");
			if (bytes <= 0) {
				if (bytes == 0) {
					puts("Client disconnected!");
				} else {
					perror("recv");
				}
				close_conn(newfd);
				break;
			}
			sprintf(message, "%s\r\n", line);
			bytes = send_msg(newfd, message);
		}
	}
	close_conn(serverfd);	/* close server socket */
	return 0;
}

