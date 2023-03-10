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
	bool processLogin(const SOCKET& currentSocket, stringstream& buffStream,
		IDatabase& db, ILogin& login);
	void sendAvailableCars(const SOCKET& currentSocket, IDatabase& db);
	bool processReservation(const SOCKET& currentSocket, stringstream& buffStream, IDatabase& db);
	void processLogout(const SOCKET& currentSocket, ILogin& login, stringstream& buffStream);
	void processRoot(const SOCKET& currentSocket, ILogin& login, stringstream& buffStream);
	void processCarAdding(const SOCKET& currentSocket, IDatabase& db, stringstream& buffStream);
	SOCKET listening;
	fd_set master;
};
