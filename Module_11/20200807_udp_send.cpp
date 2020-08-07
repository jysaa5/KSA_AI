#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 51000
#define BUFSIZE 1024

/*UDP*/
int main(void)
{
	int sockfd;
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	char sendBuffer[BUFSIZE], recvBuffer[BUFSIZE];
	int recvLen, servLen;
  
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("192.168.187.141");  // PC의 IP주소
	servAddr.sin_port = htons(PORT);

	int value = 0;
	
	while (1) 
	{
		sprintf(sendBuffer, "VALUE = %u", value);

		int sent_length = sendto(sockfd, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
		
		if (sent_length != strlen(sendBuffer)) 
		{
			printf("sendto failed");
		}

		value++;
	   
		sleep(1);
	}
	
	close(sockfd);
}

