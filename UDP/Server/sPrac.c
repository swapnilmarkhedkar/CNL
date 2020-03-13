#include<sys/socket.h>
#include<sys/types.h>

// #include<errno.h>
// #include<resolv.h>
#include<netinet/in.h>
#include<unistd.h> //for closing socket descriptor
 #include <arpa/inet.h> //for inet_addr

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_NAME_SIZE 1000
#define FILE_CONTENT_SIZE 1000000
#define PORT 8000

int main(){
	char fileName[FILE_NAME_SIZE];
	char fileContent[FILE_CONTENT_SIZE];
	int sockDesc, fileType;
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

	if(bind(sockDesc, (struct sockaddr *)&server, sizeof(server)) == 0){
		printf("Bind Successful\n");
	}

	bzero(fileName, FILE_NAME_SIZE);

	int len = sizeof(client);
	recvfrom(sockDesc, fileName, FILE_NAME_SIZE, 0, (struct sockaddr*)&client, &len);
	printf("\nFile Name : %s", fileName);

	recvfrom(sockDesc, fileContent, FILE_CONTENT_SIZE, 0,(struct sockaddr *) &client, &len);
	// printf("\nFile Content : %s", fileContent);

	FILE *p;
	p = fopen(fileName, "w");
	if(p == NULL){
		printf("\nCould not open file");
		exit(0);
	}

	fwrite(fileContent, strlen(fileContent), 1, p);
	printf("\nFile Received successfully\n");

	bzero(fileContent, strlen(fileContent));

	close(sockDesc);
	return 0;
}