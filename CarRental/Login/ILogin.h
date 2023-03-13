#pragma once
#include "../DB/IDatabase.h"
#include <iostream>
#include <string>

using namespace std;

class ILogin
{
public:
	virtual void init() = 0;
	virtual bool userExist(const string& name, const string& pass, IDatabase& db) = 0;
	virtual string getSessionToken(IDatabase& db, const string& name, const string& pass) = 0;
	virtual string getUserId(const string& token) = 0;
	virtual void logout(const string& token) = 0;
	virtual bool userIsRoot(IDatabase& db, const string& name) = 0;
	virtual bool userIsRoot(const string& token) = 0;
};