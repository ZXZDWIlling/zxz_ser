#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>

int main()
{
	int connfd;
	struct sockaddr_in addr_ser;
	connfd = socket(AF_INET, SOCK_STREAM, 0);
	int len;
	char buf[128];

	bzero(&addr_ser, sizeof(addr_ser));
	inet_pton(AF_INET, "127.0.0.1", &addr_ser.sin_addr);
	addr_ser.sin_port = htons(9913);
	addr_ser.sin_family = AF_INET;
	
	connect(connfd, (struct sockaddr *)&addr_ser, sizeof(addr_ser));
	len = read(STDIN_FILENO, buf, sizeof(buf));
	write(connfd, buf, len);
	return 0;
}
