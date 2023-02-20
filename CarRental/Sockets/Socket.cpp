#include "Socket.h"
#include <iostream>
#include <WS2tcpip.h>
#include "../Include/Errors.h"

using namespace std;

#pragma comment (lib, "ws2_32.lib")

void Socket::init()
{
	WSADATA sockets_data;								//	structer containing info about sockets
	WORD version = MAKEWORD(2, 2);						//	set the version

	int response = WSAStartup(version, &sockets_data);
	if (response != 0) {								//	error while initializing sockets
		cerr << UNABLE_INIT_SOCKET_ERR << endl;
		return;											//	quit initialization
	}
	
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);	//	creating new tcp listener
	if (listening == INVALID_SOCKET) {
		cerr << UNABLE_CREATE_SOCKET_ERR << endl;
		return;											//	quit socket creation
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;				//	bind any address

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	listen(listening, SOMAXCONN);						//	tell the socket is for listening 
	
	sockaddr_in client;									//	wait for connection
	int clientSize = sizeof(client);

	//	accept client socket
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET) {
		cerr << INVALID_CLIENT_SOCKET_ERR << endl;
		return;											//	quit connection to client
	}

	char host[NI_MAXHOST];			//	client's name
	char service[NI_MAXHOST];		//	service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);		//	clear
	ZeroMemory(service, NI_MAXHOST);	//	clear

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else 
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " << ntohs(client.sin_port) << endl;
	}

	closesocket(listening);			//	close listening port 

	char buffer[4096];				//	reading buffer

	while (true) {
		ZeroMemory(buffer, 4096);	//	clear
		int bytesReceived = recv(clientSocket, buffer, 4096, 0);	//	receive from
		if (bytesReceived == SOCKET_ERROR) {						//	check error
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}

		if (bytesReceived == 0)			//	nothing to display
		{
			cout << "Client disconnected" << endl;
			break;
		}

		send(clientSocket, buffer, bytesReceived + 1, 0);	//	echo message back to client
	}

	closesocket(clientSocket);

	WSACleanup();
}
