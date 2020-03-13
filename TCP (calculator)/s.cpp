#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#include<sys/socket.h>
#include<sys/types.h>

#include<arpa/inet.h>
#include<netinet/in.h>

// #include<bits/stdc++.h>
// #include<sys/socket.h>
// #include<sys/types.h>
// #include<netinet/in.h>
// #include<arpa/inet.h>
// #include<unistd.h>

#define PORT 8001
#define BUFFER_SIZE 1000

int main(){
	char buffer[BUFFER_SIZE];
	int serverDesc, sockDesc;
	socklen_t len;
	struct sockaddr_in server, client;

	serverDesc = socket(AF_INET, SOCK_STREAM, 0);
	if(serverDesc < 0 ){
		cout<<"\nCouldnt create socket";
		exit(0);
	}
	cout<<"\nSocket Created";

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	int status = bind( serverDesc,(struct sockaddr*)&server, sizeof(server));
	if(status<0){
		cout<<"\nCouldnt bind";
		exit(0);
	}
	cout<<"\nWaiting for client";

	len = sizeof(client);
	listen(serverDesc, 1);

	sockDesc = accept(serverDesc, (struct sockaddr*)&client, &len);
	if(sockDesc<0){
		cout<<"\nError Connecting to server";
		exit(0);
	}
	cout<<"\nConnected to Client";

	bzero(&buffer, sizeof(buffer));
	recv(sockDesc, (char*)&buffer, 6, 0 );

	// cout<<"\nReceived : "<<buffer;
	int a=0,b=0,flag=0,op;
	for(int i=0; i<strlen(buffer); i++){
		if(buffer[i] == '+'){
			op=1;
			flag=1;
		}

		if(buffer[i] == '-'){
			op=2;
			flag=1;
		}

		if(buffer[i] == '*'){
			op=3;
			flag=1;
		}

		if(buffer[i] == '/'){
			op=4;
			flag=1;
		}

		if(flag==0 && buffer[i]>='0' && buffer[i]<='9'){
			a*=10;
			a+=buffer[i]-48;
		}else if(flag==1 && buffer[i]>='0' && buffer[i]<='9'){
			b*=10;
			b+=buffer[i]-48;
		}
	}
	bzero(&buffer, sizeof(buffer));
	
	cout<<"\na : "<<a;
	cout<<"\nb : "<<b;
	cout<<"\nop : "<<op;

	string result;
	if(op==1){
		result = to_string(a+b);
	}
	strcpy(buffer,result.c_str());
	cout<<"\nBuffer : "<<buffer;
	send(sockDesc, (char*)&buffer, strlen(buffer), 0);




	cout<<endl;
	return 0;
}