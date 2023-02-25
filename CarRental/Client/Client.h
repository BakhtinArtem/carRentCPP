#pragma once
#include "IClient.h"
#include <WS2tcpip.h>

class Client : public IClient
{
public:
	void run();
private:
	SOCKET clientSocket;
};