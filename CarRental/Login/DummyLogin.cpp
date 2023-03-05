#include "Login.h"

using namespace std;

void Login::init() {
	cout << "Hi from login" << endl;
}

bool Login::userExist(const string& name, const string& pass, IDatabase& db)
{
	cout << db.findUserByNamePass(name, pass) << endl;
	cout << (db.findUserByNamePass(name, pass) >= 0) << endl;
	return db.findUserByNamePass(name, pass) >= 0;		//	check if some index was found
}
