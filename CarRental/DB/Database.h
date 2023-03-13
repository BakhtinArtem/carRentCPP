#pragma once
#include "IDatabase.h"

class Database : public IDatabase
{
public:
	void init();
	int findUserByNamePass(const string& name, const string& pass);
	string getAllCars();
	bool carIsReserved(const string& id);
	bool existOrderWithCarId(const string& id);
	bool userIsRoot(const string& name);
	void addCar(const string& carName);
private:
	int usersId;
	int carsId;
	int orderId;
};