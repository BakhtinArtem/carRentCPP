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
	string getSessionToken(const string& name, const string& pass);
private:
	unordered_map<string, vector<string>> sessionStorage;
};