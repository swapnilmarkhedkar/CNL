#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main(){


	int count=-1,ch;

	string no, time, source, destination, protocol,length, info, protocolChoice;

	cout<<"\n1. IP\n2. TCP\n3. UDP\n4. ARP";
	cin>>ch;

	switch(ch)
	{
		case 1:
			protocolChoice="\"ICMPv6\"";
			break;

		case 2:
			protocolChoice="\"TCP\"";
			break;

		case 3:
			protocolChoice="\"UDP\"";
			break;

		case 4:
			protocolChoice="\"ARP\"";
			break;
	}

	ifstream f;
	f.open("a.csv", ios::in);

	while(f.good()){
		getline(f,no,',');
		getline(f,time,',');
		getline(f,source,',');
		getline(f,destination,',');
		getline(f,protocol,',');
		getline(f,length,',');
		getline(f,info,'\n');


		if(protocol == protocolChoice || protocol == "Protocol"){
			cout<<setw(12)<<left<<string(time, 1, time.length()-2);
			cout<<setw(30)<<left<<string(source, 1, source.length()-2);
			cout<<setw(30)<<left<<string(destination, 1, destination.length()-2);
			cout<<setw(8)<<left<<string(protocol, 1, protocol.length()-2);
			cout<<setw(8)<<left<<string(length, 1, length.length()-2);
			cout<<string(info, 1, info.length()-2)<<"\n";
			count++;
		}
	}
		f.close();
		cout<<"\nCount : "<<count;

}