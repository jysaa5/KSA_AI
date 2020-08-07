#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*TCP*/
int main(void)
{
	int sockfd;
	struct sockaddr_in serv_addr;

	char message[30];
	int str_len;

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.187.141");   	// PC의 IP주소
	serv_addr.sin_port = htons(52000);

	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) 
	{
		printf("connect() error");
	}
	
	str_len = read(sockfd, message, sizeof(message) - 1);
	message[str_len] = '\0';
	
	if (str_len == -1)
	{
		printf("read() error");
	}

	printf("Message from server: %s\n", message);

	close(sockfd);
}
