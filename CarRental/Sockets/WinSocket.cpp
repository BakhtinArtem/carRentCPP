#include "WinSocket.h"
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "../Include/Utils.h"
#include "../Include/Errors.h"

using namespace std;

void WinSocket::init()
{
	WSADATA sockets_data;								//	structer containing info about sockets
	WORD version = MAKEWORD(2, 2);						//	set the version

	int response = WSAStartup(version, &sockets_data);
	if (response != 0) {								//	error while initializing sockets
		cerr << UNABLE_INIT_SOCKET_ERR << endl;
		return;											//	quit initialization
	}
	
	this->listening = socket(AF_INET, SOCK_STREAM, 0);	//	creating new tcp listener
	if (this->listening == INVALID_SOCKET) {			//	error while creating listener
		cerr << UNABLE_CREATE_SOCKET_ERR << endl;
		WSACleanup();
		return;											//	quit socket creation
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;							//	ipv4
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;				//	bind any address

	bind(this->listening, (sockaddr*)&hint, sizeof(hint));
}

void WinSocket::run(IDatabase& db, ILogin& login) {
	initMasterSet();
	while (true) {
		fd_set copy = this->master;						//	create a copy of structer
		int socketNumber = select(0, &copy,				//	copy will be destroyed
			nullptr, nullptr, nullptr);

		for (int i = 0; i < socketNumber; i++) {
			SOCKET currentSocket = copy.fd_array[i];	//	i-th element

			if (currentSocket == this->listening) {
				acceptClient();
			}
			else {
				processRequest(currentSocket, db, login);
			}
		}
	}
	WSACleanup();
}

void WinSocket::initMasterSet()
{
	listen(this->listening, SOMAXCONN);			//	tell the socket is for listening 
	FD_ZERO(&this->master);						//	clear master set
	FD_SET(this->listening, &this->master);		//	add listener to set
}

void WinSocket::acceptClient()
{
	//	accept new connection
	SOCKET client = accept(this->listening, nullptr, nullptr);
	FD_SET(client, &this->master);			//	add client to list of connected clients(so we can listen again)
	string welcomeMsg = SUCCESSFUL_CONNECTION + "\n";
	send(client, welcomeMsg.c_str(), welcomeMsg.size(), 0);	//	send ok response
}

void WinSocket::processRequest(const SOCKET& currentSocket, IDatabase& db, ILogin& login)
{
	char buff[4096];			//	buffer for new request
	ZeroMemory(buff, 4096);

	int bytes = recv(currentSocket, buff, 4096, 0);	//	recieve request
	if (bytes <= 0) {								//	no message
		disconnectClient(currentSocket);
	}

	string stringBuffer(buff);			//	convert buff to string
	string request;
	stringstream buffStream(stringBuffer);
	getline(buffStream, request, delimetr);
				
	if (request == REQUEST_LOGIN) {
		processLogin(buffStream, db, login);
	}
	else if (request == REQUEST_NEW_USER) {
		
	}
}

void WinSocket::disconnectClient(const SOCKET& currentSocket)
{
		closesocket(currentSocket);
		FD_CLR(currentSocket, &this->master);		//	clear from connected clients
}

void WinSocket::processLogin(stringstream& buffStream, IDatabase& db, ILogin& login)
{
		string name, pass;
		getline(buffStream, name, delimetr);
		getline(buffStream, pass, delimetr);
		login.userExist(db);
		cout << "log: " << name << " pas: " << pass << endl;
}



