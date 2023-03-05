#define WIN32_LEAN_AND_MEAN

//	User
#include "../Include/Errors.h"
#include "../Include/Utils.h"
#include "Client.h"

//	Sockets
#include <Windows.h>
#include <WinSock2.h>

#include <iostream>
#include <string>

using namespace std;

#pragma comment (lib, "ws2_32.lib")

void Client::run() {
	WSADATA socket_data;
	ADDRINFO hints;
	ADDRINFO* addrResult = NULL;
	int response;
	this->clientSocket = INVALID_SOCKET;				//	set socket error before init
	
	response = WSAStartup(MAKEWORD(2,2), &socket_data);
	if (response != 0) {								//	error while initializing socket
		cerr << UNABLE_INIT_SOCKET_ERR << endl;
		return;											//	quit initialization
	}

	ZeroMemory(&hints, sizeof(hints));					//	set zero to all fields -> they will be ignored
	hints.ai_family = AF_INET;							//	ipv4
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;					//	tcp protocol

	response = getaddrinfo("localhost", "54000", &hints, &addrResult);
	if (response != 0) {								//	error while creating socker
		cerr << UNABLE_CREATE_SOCKET_ERR << endl;
		WSACleanup();									//	clean wsa
		return;
	}

	this->clientSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
	if (this->clientSocket == INVALID_SOCKET) {
		cerr << UNABLE_CREATE_SOCKET_ERR << endl;
		freeaddrinfo(addrResult);
		WSACleanup();
		return;
	}

	response = connect(this->clientSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
	if (response == SOCKET_ERROR) {
		cerr << CONNECT_IS_NOT_ESTAMBLISHED << endl;
		closesocket(this->clientSocket);
		this->clientSocket = INVALID_SOCKET;
		freeaddrinfo(addrResult);
		WSACleanup();
		return;
	}

	char buff[4096];
	ZeroMemory(buff, 4096);
		
	recv(this->clientSocket, buff, 4096, 0);
	cout << buff << endl;		//	get response from server
	this->state = login;

	while (true) {
		ZeroMemory(buff, 4096);
		
		if (this->state == login) {
			this->token = this->processLogin(buff);
			this->state = process;
			cout << "this is: " << this->token << endl;
		}
		else if (this->state == process) {

		}
	}
}

string Client::processLogin(char* buff)
{
	string data;
	getline(cin, data);
	//	send login info
	send(this->clientSocket, data.c_str(), data.size(), 0);
	//	get response
	recv(this->clientSocket, buff, 4096, 0);
	if (buff == UNSUCCESSFUL_LOGIN_RESPONSE) {
		return "";
	}

	return string(buff);		//	wrap buffer to string
}



