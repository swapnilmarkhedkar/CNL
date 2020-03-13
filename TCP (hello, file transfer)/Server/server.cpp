#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#include<sys/socket.h>
#include<sys/types.h>

#include<arpa/inet.h>
#include<netinet/in.h>

//#include<bits/stdc++.h>
//#include<sys/socket.h>
//#include<sys/types.h>
//#include<netinet/in.h>
//#include<arpa/inet.h>
//#include<unistd.h>

#define PORT 8001
#define FILE_NAME_SIZE 100
#define FILE_CONTENT_SIZE 1000
#define BUFFER_SIZE 1000

int main(){

	char fileName[FILE_NAME_SIZE];
	char fileContent[FILE_CONTENT_SIZE];
	char buffer[BUFFER_SIZE];
	int serverDesc, sockDesc;
	struct sockaddr_in server, client;
	socklen_t len;

	serverDesc = socket( AF_INET, SOCK_STREAM, 0);
	if(serverDesc == -1){
		cout<<"\nError creating socket";
		exit(0);
	}
	cout<<"\nSocket Created";

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	// server.sin_addr.s_addr = inet_addr("192.168.0.108");
	server.sin_port = htons(PORT);

	//Bind
	int bindStatus = bind(serverDesc, (struct sockaddr*)&server, sizeof(server));
	if(bindStatus < 0){
		cout<<"\nError during bind";
		exit(0);
	}
	else
		cout<<"\nWaiting for Client";


	//Connect with Client
	listen(serverDesc,1);
	len = sizeof(client);

	sockDesc = accept(serverDesc, (struct sockaddr*)&client, &len);
	if(sockDesc < 0){
		cout<<"\n Could not connect with client";
		exit(0);
	}
	cout<<"\nConnection Established with client";






	//File Transfer
	ofstream f;
	bzero(&fileName, sizeof(fileName));
	recv(sockDesc, (char*)&fileName, 10, 0);
	// listen(serverDesc,1);
	f.open(fileName , ios::out);
	if(f.is_open())
		cout<<"\nOpened Successfully!";

	cout<<"\nFileName : "<<fileName;
	bzero(&fileContent, sizeof(fileContent));
	bzero(&buffer, sizeof(buffer));
	recv(sockDesc, (char*)&buffer, 50, 0);

	cout<<"\nFile : "<<buffer;
	f<<buffer<<endl;
	f.close();


	//Chat
	bzero(&buffer, sizeof(buffer));
	recv(sockDesc, (char*)&buffer, sizeof(buffer),0);
	cout<<"\nClient says '"<<buffer<<"'";

	string data = "Hello Client!";
	bzero(&buffer, sizeof(buffer));
	strcpy(buffer, data.c_str());
	send(sockDesc, (char*)&buffer, sizeof(buffer), 0);


	cout<<endl;
	//close desc
	return 0;
}
