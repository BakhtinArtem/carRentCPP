#include "IClient.h"
#include <WS2tcpip.h>
#include <iostream>
#include <string>

using namespace std;

enum CLIENT_STATE {
	login,
	process
};

class Client : public IClient
{
public:
	void run();
private:
	string processLogin(char* buff);
	SOCKET clientSocket;
	CLIENT_STATE state;
	string token;
};