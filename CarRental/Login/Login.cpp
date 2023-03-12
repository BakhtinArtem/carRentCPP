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

string Login::getSessionToken(IDatabase& db, const string& name, const string& pass)
{
	hash<string> hasher;
	size_t token = hasher(name + pass);
	const int userId = db.findUserByNamePass(name, pass);
	if (userIsRoot(db, name)) {	//	add to root users in current session
		rootUsers.push_back(to_string(userId));
	}
	this->sessionStorage.insert({ to_string(token), to_string(userId)});
	return to_string(token);
}



string Login::getUserId(const string& token)
{
	return this->sessionStorage.at(token);
}

bool Login::userIsRoot(IDatabase& db, const string& name)
{
	if (db.userIsRoot(name)) {
		return true;
	}
	else {
		return false;
	}
}

void Login::logout(const string& token)
{
	this->sessionStorage.erase(token);
}
