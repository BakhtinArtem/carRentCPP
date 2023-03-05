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
	virtual string getSessionToken(const string& name, const string& pass) = 0;
};