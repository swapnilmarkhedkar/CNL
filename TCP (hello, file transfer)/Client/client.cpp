#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<arpa/inet.h>

//#include<arpa/inet.h>
//#include<unistd.h>
//#include <netdb.h>
//#include<fstream>
//#include <sys/stat.h>

#define FILE_NAME_SIZE 100
#define FILE_CONTENT_SIZE 1000
#define PORT 8001
#define BUFFER_SIZE 1000

int main(){
	char fileName[FILE_NAME_SIZE];
	char fileContent[FILE_CONTENT_SIZE];
	char buffer[BUFFER_SIZE];

	int sockDesc;
	struct sockaddr_in server, client;

	sockDesc = socket(AF_INET, SOCK_STREAM, 0);

	//connect
	bzero((char*)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	// server.sin_addr.s_addr = inet_addr("192.168.0.108");
	server.sin_port = htons(PORT);

	if(sockDesc == -1){
		cout<<"\nError in creating socket!";
		exit(0);
	}
	cout<<"\nSocket Created";

	int status = connect(sockDesc, (struct sockaddr * ) &server, sizeof(server));
	if(status<0){
		cout<<"\nCould not connect to server";
		exit(0);
	}

	cout<<"\nConnected to Server";



	//File Transfer
	cout<<"\nEnter File you wish to Transfer";
	cin>>fileName;
	ifstream f;
	f.open(fileName, ios::in);
	while(!f.is_open()){
		cout<<"\nError Opening file\nRe-enter file";
		cin>>fileName;
		f.open(fileName, ios::in);
	}
	f.close();
	cout<<"\nFile Opened!";

	bzero(&buffer, sizeof(buffer));
	strcpy(buffer, fileName);
	send(sockDesc, (char*)&buffer, 10, 0);

	string line;
	bzero(&fileContent, sizeof(fileContent));
	f.open(fileName,ios::in);
	while(f){
		getline(f, line);
		strcat(fileContent, line.c_str());
		strcat(fileContent, "\n");
	}
	f.close();

	bzero(&buffer, sizeof(buffer));
	strcpy(buffer, fileContent);
	cout<<"\nFile Content : "<<buffer;
	send(sockDesc, (char*)&buffer, 50, 0);


	//Chat
	bzero(&buffer, sizeof(buffer));
	string data;
	cout<<"\nGreet Server : ";
	cin>>data; //Or getline(cin, data);
	strcpy(buffer, data.c_str());	
	send(sockDesc, (char*)&buffer, sizeof(buffer), 0);

	bzero(&buffer, sizeof(buffer));
	recv(sockDesc, (char*)&buffer, sizeof(buffer), 0);
	cout<<"\nServer says '"<<buffer<<"'";



	cout<<endl;
	//close desc
	return 0;
}
