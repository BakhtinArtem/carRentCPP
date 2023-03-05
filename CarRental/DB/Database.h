#pragma once
#include "IDatabase.h"

class Database : public IDatabase
{
public:
	void init();
	int findUserByNamePass(const string& name, const string& pass);
};