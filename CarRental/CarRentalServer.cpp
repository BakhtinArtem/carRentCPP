#include "CarRental.h"
#include "Processor/Processor.h"
#include "DB/Database.h"
#include "Login/Login.h"
#include "Sockets/WinSocket.h"

using namespace std;

/*
*	TODOs:
	[] - Destructor in each class
*/

Processor processor;
Database db;
Login login;
WinSocket sockets;

int main()
{
	processor.init(sockets, db, login);
	processor.processConnection(sockets, db, login);
	return 0;
}
