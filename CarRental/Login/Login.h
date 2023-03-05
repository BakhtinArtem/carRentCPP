#pragma once
#include "ILogin.h"
#include "../DB/Database.h"

class Login : public ILogin
{
public:
	void init();
	bool userExist(const string& name, const string& pass, IDatabase& db);
};