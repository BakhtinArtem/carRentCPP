#pragma once
#include "../DB/IDatabase.h"

class ILogin
{
public:
	virtual void init() = 0;
	virtual void userExist(IDatabase& db) = 0;
};