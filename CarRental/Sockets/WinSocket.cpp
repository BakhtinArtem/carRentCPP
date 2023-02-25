#include "WinSocket.h"
#include <iostream>
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

void WinSocket::run(IDatabase const& db, ILogin const& login) {
	listen(this->listening, SOMAXCONN);					//	tell the socket is for listening 
	
	fd_set master;										//	master set
	
	FD_ZERO(&master);
	FD_SET(this->listening, &master);					//	add listener to set

	while (true) {
		fd_set copy = master;							//	create a copy of structer
		int socketNumber = select(0, &copy,				//	copy will be destroyed
			nullptr, nullptr, nullptr);

		for (int i = 0; i < socketNumber; i++) {
			SOCKET currentSocket = copy.fd_array[i];	//	i-th element

			if (currentSocket == this->listening) {
				//	accept new connection
				SOCKET client = accept(this->listening, nullptr, nullptr);
				FD_SET(client, &master);				//	add client to list of connected clients(so we can listen again)
				string welcomeMsg = "Welcome to the chat\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size(), 0);
			}
			else {
				//	accept new message
				char buff[4096];
				ZeroMemory(buff, 4096);

				int bytes = recv(currentSocket, buff, 4096, 0);
				cout << buff << endl;
				if (bytes <= 0) {		//	no message
					closesocket(currentSocket);
					FD_CLR(currentSocket, &master);		//	clear from connected clients
				}
				else
				{
					for (int i = 0; i < master.fd_count; i++) {
						SOCKET outSock = master.fd_array[i];
						//	dont sent to listener and current socket
						if (outSock != this->listening && outSock != currentSocket) {
							send(outSock, buff, bytes, 0);
						}
					}
				}
			}
		}
	}
	WSACleanup();
}
