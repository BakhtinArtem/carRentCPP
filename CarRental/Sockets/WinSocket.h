#pragma once

#include "ISocket.h"
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

class WinSocket : public ISocket
{
public:
	void init();
	void run(IDatabase& db, ILogin& login);
private:
	void initMasterSet();
	void acceptClient();
	void processRequest(const SOCKET& currentSocket, IDatabase& db, ILogin& login);
	void disconnectClient(const SOCKET& currentSocket);
	void processLogin(const SOCKET& currentSocket, stringstream& buffStream,
		IDatabase& db, ILogin& login);
	SOCKET listening;
	fd_set master;
};
