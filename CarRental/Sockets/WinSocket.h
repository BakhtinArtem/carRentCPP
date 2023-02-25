#pragma once

#include "ISocket.h"
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

class WinSocket : public ISocket
{
public:
	void init();
	void run(IDatabase const& db, ILogin const& login);
private:
	SOCKET listening;
};
