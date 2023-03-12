#pragma once
#include "ILogin.h"
#include "../DB/Database.h"
#include <unordered_map>
#include <vector>

using namespace std;

class Login : public ILogin
{
public:
	void init();
	bool userExist(const string& name, const string& pass, IDatabase& db);
	string getSessionToken(IDatabase& db, const string& name, const string& pass);
	string getUserId(const string& token);
	bool userIsRoot(IDatabase& db, const string& name);
	void logout(const string& token);
private:
	unordered_map<string, string> sessionStorage;
	vector<string> rootUsers;
};