#include "Processor.h"

using namespace std;

void Processor::processConnection(ISocket &socket, IDatabase const& db, ILogin const& login) {
	socket.run(db, login);
}

void Processor::init(ISocket& socket, IDatabase& db, ILogin& login) {
	socket.init();
	db.init();
	login.init();
}
