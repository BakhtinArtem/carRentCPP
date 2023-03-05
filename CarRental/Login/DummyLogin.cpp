#include "Login.h"
#include <sstream>

using namespace std;

void Login::init() {
	cout << "Hi from login" << endl;
}

bool Login::userExist(const string& name, const string& pass, IDatabase& db)
{
	return db.findUserByNamePass(name, pass) >= 0;		//	check if some index was found
}

string Login::getSessionToken(const string& name, const string& pass)
{
	hash<string> hasher;
	size_t t = hasher(name + pass);
	vector<string> pair = {name, pass};		//	container with vector and pass
	this->sessionStorage.insert({ to_string(t), pair });
	return to_string(t);
}
