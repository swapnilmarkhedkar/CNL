#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#include<sys/socket.h>
#include<sys/types.h>

#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 8001
#define BUFFER_SIZE 10

int main(){
	char buffer[BUFFER_SIZE];
	int sockDesc;
	socklen_t len;
	struct sockaddr_in server, client;

	sockDesc = socket(AF_INET, SOCK_STREAM, 0);
	if(sockDesc < 0 ){
		cout<<"\nCouldnt create socket";
		exit(0);
	}
	cout<<"\nSocket Created";
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	int status = connect( sockDesc,(struct sockaddr*)&server, sizeof(server));
	if(status<0){
		cout<<"\nCouldnt connect";
		exit(0);
	}
	cout<<"\nConnected to Server";

	bzero(&buffer, sizeof(buffer));
	cout<<"\nEnter Arithmetic : ";
	cin>>buffer;

	send(sockDesc, (char*)buffer, strlen(buffer), 0);

	bzero(&buffer, sizeof(buffer));
	recv(sockDesc, (char*)buffer, 5, 0);
	cout<<"\nOutput : "<<buffer;



	cout<<endl;
	return 0;
}