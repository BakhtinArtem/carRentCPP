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
	if (!configureConnection()) {
		return;				//	configuration was successful 
	}
	processConection();
}


bool Client::configureConnection()
{
	WSADATA socket_data;
	ADDRINFO hints;
	ADDRINFO* addrResult = NULL;
	int response;
	this->clientSocket = INVALID_SOCKET;				//	set socket error before init
	
	response = WSAStartup(MAKEWORD(2,2), &socket_data);
	if (response != 0) {								//	error while initializing socket
		cerr << UNABLE_INIT_SOCKET_ERR << endl;
		return false;									//	quit initialization
	}

	ZeroMemory(&hints, sizeof(hints));					//	set zero to all fields -> they will be ignored
	hints.ai_family = AF_INET;							//	ipv4
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;					//	tcp protocol

	response = getaddrinfo("localhost", "54000", &hints, &addrResult);
	if (response != 0) {								//	error while creating socker
		cerr << UNABLE_CREATE_SOCKET_ERR << endl;
		WSACleanup();									//	clean wsa
		return false;
	}

	this->clientSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
	if (this->clientSocket == INVALID_SOCKET) {
		cerr << UNABLE_CREATE_SOCKET_ERR << endl;
		freeaddrinfo(addrResult);
		WSACleanup();
		return false;
	}

	response = connect(this->clientSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
	if (response == SOCKET_ERROR) {
		cerr << CONNECT_IS_NOT_ESTAMBLISHED << endl;
		closesocket(this->clientSocket);
		this->clientSocket = INVALID_SOCKET;
		freeaddrinfo(addrResult);
		WSACleanup();
		return false;
	}
	return true;		//	configuartion was successful
}


void Client::processConection()
{
	char buff[4096];
	ZeroMemory(buff, 4096);
		
	recv(this->clientSocket, buff, 4096, 0);
	cout << buff << endl;		//	get positivr response from server
	this->state = login;

	while (true) {
		ZeroMemory(buff, 4096);
		
		if (this->state == login) {
			this->token = this->processLogin(buff);
			if (this->state == error) {
				cout << "Login was unsuccessful" << endl;
				return;			//	login was unsuccessful
			}
			this->isRoot = isUserRoot(buff);
			this->state = idle;
		}
		else if (this->state == reservation) {
			processReservation(buff);
			if (this->state == error) {
				cout << "Reservation was unsuccessful" << endl;
				return;
			}
			this->state = idle;
		}
		else if (this->state == idle) {
			processIdle();
			if (this->state == error) {
				cout << "Option does not exist" << endl;
				return;
			}
		}
		else if (this->state == logout) {
			processLogout();
			return;
		}
		else if (this->state == addCar) {
			processCarAdding(buff);
			this->state = idle;
		}
	}
}

void Client::processReservation(char* buff)
{
	// send request to get list cars
	string request = REQUEST_CARS_LIST;
	send(this->clientSocket, request.c_str(), request.size(), 0);
	request.clear();	//	clear request for futher use

	recv(this->clientSocket, buff, 4096, 0);	//	get cars list
	cout << buff << endl;
	cout << "Choose car id to reserve:" << endl;
	string id;
	getline(cin, id);
	request = REQUEST_RESERVATION + delimetr + this->token + delimetr + id;
	//	send reservation request to server
	send(this->clientSocket, request.c_str(), request.size(), 0);
	//	get response from server
	ZeroMemory(buff, 4096);
	recv(this->clientSocket, buff, 4096, 0);
	if (buff == ERROR_RESPONSE) {
		this->state = error;
	}
}

void Client::processIdle()
{
	if (this->isRoot) {
		cout << ROOT_OPTIONS << endl;
	}
	else
	{
		cout << CLIENT_OPTIONS << endl;
	}
	string response;
	getline(cin, response);
	if (response == "1") {
		if (this->isRoot) {	//	other response if root
			this->state = addCar;
		}
		else {
			this->state = reservation;
		}
	}
	else if (response == "2") {
		if (this->isRoot) {	//	other response if root
			this->state = deleteCar;
		}
		else {
			this->state = endReservation;
		}
	}
	else if (response == "3") {
		this->state = logout;
	}
	else {
		this->state = error;
	}
}

void Client::processLogout()
{
	string request = REQUEST_LOGOUT + delimetr + token;
	send(this->clientSocket, request.c_str(), request.size(), 0);
}

bool Client::isUserRoot(char* buff)
{
	string request = REQUEST_USER_IS_ROOT + delimetr + this->token;
	send(this->clientSocket, request.c_str(), request.size(), 0);
	ZeroMemory(buff, 4096);
	recv(this->clientSocket, buff, 4096, 0);
	if (buff == TRUE_RESPONE) {
		return true;
	}
	return false;
}

void Client::processCarAdding(char* buff)
{
	cout << "Wrtie new car name:" << endl;
	string carName;
	getline(cin, carName);
	string request = 
		REQUEST_ADD_CAR + delimetr + this->token + delimetr + carName;
	send(this->clientSocket, request.c_str(), request.size(), 0);
	recv(this->clientSocket, buff, 4096, 0);	//	recv OK response
}

string Client::processLogin(char* buff)
{
	string login, pass, request;
	cout << "Please enter login:" << endl;
	getline(cin, login);
	cout << "Please enter password:" << endl;
	getline(cin, pass);
	request = REQUEST_LOGIN + delimetr + login + delimetr + pass;
	//	send request to sever
	send(this->clientSocket, request.c_str(), request.size(), 0);
	//	get response
	recv(this->clientSocket, buff, 4096, 0);
	if (buff == UNSUCCESSFUL_LOGIN_RESPONSE) {
		this->state = error;		//	error while login
		return "";					//	empty token
	}
	return string(buff);		//	wrap buffer to string
}



