#include<sys/types.h>
#include<sys/socket.h>

// #include<errno.h>
#include<resolv.h> // for fopen, fgets and fclose 
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <arpa/inet.h>

#define FILE_NAME_SIZE 1000
#define FILE_CONTENT_SIZE 1000000
#define PORT 8000

int main(){
	char fileName[FILE_NAME_SIZE];
	char fileContent[FILE_CONTENT_SIZE];
	int sockDesc, fileType, len;
	struct sockaddr_in server, client;

	sockDesc = socket(AF_INET, SOCK_DGRAM, 0);

	if(sockDesc==-1){
		printf("Error while creating socket\n");
		exit(0);
	}
	printf("Socket Created!\n");

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.0.108");
	server.sin_port = htons(PORT);

	bzero(&fileName, FILE_NAME_SIZE);
	printf("Enter name of file you wish to send to server\n");
	scanf("%s" ,fileName);

	sendto(sockDesc, fileName, strlen(fileName), 0, (struct sockaddr *) &server, sizeof(server));
	
	FILE *p;
	p = fopen(fileName, "r");
	if(p == NULL){
		printf("Could not open file\n");
		exit(0);
	}

	while(fgets(fileContent, FILE_CONTENT_SIZE, p) != NULL)

	printf("%s\n", fileContent);
	fclose(p);

	sendto(sockDesc, fileContent, strlen(fileContent), 0, (struct sockaddr *)&server, sizeof(server));

	close(sockDesc);
	return 0;
}