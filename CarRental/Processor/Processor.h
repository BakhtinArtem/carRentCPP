#pragma once
#include "../Sockets/ISocket.h"
#include "../DB/IDatabase.h"
#include "../Login/ILogin.h"

class Processor
{
public:
	void processConnection(ISocket &socket, IDatabase& db, ILogin& login);
	void init(ISocket& socket, IDatabase& db, ILogin& login);
};