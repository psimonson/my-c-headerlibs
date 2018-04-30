#include "../common/sock_help.h"

int main(void)
{
	SERVER_INFO;

	sockfd = create_server(0, 5000, "0.0.0.0");
	if (sockfd == BAD_SOCKET)
		return 1;
	newfd = accept_conn(sockfd);
	if (sockfd == BAD_SOCKET)
		return 1;
	send_msg(newfd, "Hello world, from simple server socket app.\r\n");
	close_conn(newfd);
	close_conn(sockfd);
	return 0;
}
