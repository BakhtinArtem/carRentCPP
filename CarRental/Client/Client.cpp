#define WIN32_LEAN_AND_MEAN

//	User
#include "../Include/Errors.h"
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

	while (true) {

		string msg;
		getline(cin, msg);
		send(this->clientSocket, msg.c_str(), msg.size(), 0);
		/*char buff[4096];
		ZeroMemory(buff, 4096);

		int bytes = recv(this->clientSocket, buff, 4096, 0);
		cout << buff;*/
	}
}
