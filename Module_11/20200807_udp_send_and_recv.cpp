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
/*Echo Server*/
int main()
{
	int sockfd;
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	int clntLen;
	int recvLen;
	char sendBuffer[BUFSIZE], recvBuffer[BUFSIZE];
	int servLen;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servAddr, 0, sizeof(servAddr));
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(51000);

	if (bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) 
	{
		printf("bind failed");
	}

	while (1) 
	{
		clntLen = sizeof(clntAddr);
		
		//recvLen: 블로킹 함수
		if ((recvLen = recvfrom(sockfd, recvBuffer, BUFSIZE - 1, 0, (struct sockaddr*)&clntAddr, (socklen_t*)&clntLen)) == -1) 
		{
			printf("recvfrom failed");
		}
	   
		
		memcpy(sendBuffer, recvBuffer, recvLen);
		
		
		int sent_length = sendto(sockfd, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr*)&clntAddr, sizeof(clntAddr));
		
		if (sent_length != strlen(sendBuffer)) 
		{
			printf("sendto failed");
		}
		
	}
}
