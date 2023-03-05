#pragma once
#include "ILogin.h"
#include "../DB/Database.h"

class Login : public ILogin
{
public:
	void init();
	void userExist(IDatabase& db);
};