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
				cout << "inside accept" << endl;
				acceptClient();
			}
			else {
				cout << "inside process" << endl;
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
	SOCKET client = accept(this->listening, nullptr, nullptr);	//	accept new connection
	FD_SET(client, &this->master);								//	add client to list of connected clients(so we can listen again)
	//	send ok response
	send(client, SUCCESSFUL_CONNECTION_RESPONSE.c_str(), SUCCESSFUL_CONNECTION_RESPONSE.size(), 0);
}

void WinSocket::processRequest(const SOCKET& currentSocket, IDatabase& db, ILogin& login)
{
	char buff[4096];								//	buffer for new request
	ZeroMemory(buff, 4096);

	int bytes = recv(currentSocket, buff, 4096, 0);	//	recieve request
	if (bytes <= 0) {								//	no message
		cout << "inside disconnect" << endl;
		disconnectClient(currentSocket);
	}

	string stringBuffer(buff);						//	convert buff to string
	string request;
	stringstream buffStream(stringBuffer);
	getline(buffStream, request, delimetr);
				
	if (request == REQUEST_LOGIN) {
		cout << "inside login" << endl;
		if (processLogin(currentSocket, buffStream, db, login)) {
			sendAvailableCars(currentSocket, db);
		}
	}
	else if (request == REQUEST_NEW_USER) {
		cout << "inside request" << endl;
	}
	else if (request == REQUEST_RESERVATION) {
		if (!processReservation(currentSocket, buffStream, db)) {
			cout << "PRObbBBlem" << endl;
			return;		//	can not reserv
		}
		send(currentSocket, OK_RESPONE.c_str(), OK_RESPONE.size(), 0);
	}
}

bool WinSocket::processReservation(const SOCKET& currentSocket, stringstream& buffStream, IDatabase& db)
{
	string token, id;
	getline(buffStream, token, delimetr);
	getline(buffStream, id, delimetr);
	cout << "GOT " << token << " " << id << endl;
	return true;
}

void WinSocket::sendAvailableCars(const SOCKET& currentSocket, IDatabase& db) {
	//	const string cars = db.getAllCars();
	const string cars = "0;skoda;busy\n1;toyota;available";
	send(currentSocket, cars.c_str(), cars.size(), 0);
}


void WinSocket::disconnectClient(const SOCKET& currentSocket)
{
		closesocket(currentSocket);
		FD_CLR(currentSocket, &this->master);		//	clear from connected clients
}

bool WinSocket::processLogin(const SOCKET& currentSocket, stringstream& buffStream,
	IDatabase& db, ILogin& login)
{
		string name, pass;
		getline(buffStream, name, delimetr);
		getline(buffStream, pass, delimetr);
		if (login.userExist(name, pass, db)) {
			cout << "yes user" << endl;
			string token = login.getSessionToken(name, pass);
			cout << token << endl;
			send(currentSocket, token.c_str(),
				token.size(), 0);
			return true;		//	login was successful
		}
		else {
			cout << "no user" << endl; 
			send(currentSocket, UNSUCCESSFUL_LOGIN_RESPONSE.c_str(),
				UNSUCCESSFUL_LOGIN_RESPONSE.size(), 0);
			return false;		//	login was unsuccessful
		}
}