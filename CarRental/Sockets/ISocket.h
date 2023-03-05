#pragma once
#include "../DB/IDatabase.h"
#include "../Login/ILogin.h"

#include <iostream>

using namespace std;

class ISocket
{
public:
	virtual void init() = 0;
	virtual void run(IDatabase& db, ILogin& login) = 0;
};