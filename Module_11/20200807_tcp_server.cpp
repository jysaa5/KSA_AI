#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*TCP*/
int main(void)
{
	struct sockaddr_in server_addr, client_addr;

	int server_fd, client_fd;
	
	server_fd = socket(AF_INET, SOCK_STREAM, 0); 

	memset(&server_addr, 0, sizeof(server_addr));
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(51000);

	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Server : bind() faild.\n");
	}
 
	if (listen(server_fd, 5) < 0)
	{
		printf("Server : listen() faild.\n");
	}
	
	printf("Server : waiting connection...\n");
	
	char buffer[1024];		
	int addr_len, msg_size;
	
	addr_len = sizeof(client_addr);
	
	while (1)
	{
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addr_len);
		if (client_fd < 0)
		{
			printf("Server: accept failed.\n");
			exit(0);
		}
		
		char client_addr_str[32];

		inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_addr_str, sizeof(client_addr_str));
		printf("Server : %s client connected.\n", client_addr_str);
    
		msg_size = read(client_fd, buffer, 1024);
		
		printf("Received (%u bytes) : %s\n", msg_size, buffer);
		
		write(client_fd, buffer, msg_size);
		
		close(client_fd);
		printf("Server : %s client closed.\n", client_addr_str);
	}
	
	close(server_fd);
	
}
