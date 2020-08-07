#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <wiringPi.h>

/*TCP*/
int main(void)
{
	int sockfd;
	struct sockaddr_in serv_addr;

	char message[30];
	int str_len;
	
	wiringPiSetup();
	// Pin = 28

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.187.141");    	// PC의 IP주소
	serv_addr.sin_port = htons(52000);

	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) 
	{
		printf("connect() error");
	}
	
	
	while (true)
	{
		str_len = read(sockfd, message, sizeof(message) - 1);
		message[str_len] = '\0';
      
		if (str_len == -1)
		{
         
		}
		else if (str_len > 0)
		{
			printf("Message from server: %s\n", message);
         
			if (!strcmp(message, "LED ON"))
			{
				printf("LED ON\n");
				digitalWrite(28, HIGH);
            
			}
			else if (!strcmp(message, "LED OFF"))
			{
				printf("LED LOW\n");
				digitalWrite(28, LOW);
			}
         
		}
      
		int pre_button_state = -1;
		int button_state = digitalRead(29);
      
		if (button_state != pre_button_state)
		{
			if (button_state == 1)
			{
				char send_msg[32];
				sprintf(send_msg, "Button Pushed");
				write(sockfd, send_msg, strlen(send_msg));
            
			}
         
		}

		pre_button_state = button_state;
      
      
	}
	

	close(sockfd);
}
