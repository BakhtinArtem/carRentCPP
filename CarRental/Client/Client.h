#include "IClient.h"
#include <WS2tcpip.h>
#include <iostream>
#include <string>

using namespace std;

enum CLIENT_STATE {
	login,
	reservation,
	endReservation,
	idle,
	logout,
	addCar,
	deleteCar,
	error
};

class Client : public IClient
{
public:
	void run();
	void processConection();
	bool configureConnection();
	void processReservation(char* buff);
	void processIdle();
	void processLogout();
	bool isUserRoot(char* buff);
	void processCarAdding(char* buff);
private:
	bool isRoot;
	string processLogin(char* buff);
	SOCKET clientSocket;
	CLIENT_STATE state;
	string token;
};