#pragma once
#include <string>
#include <iostream>

using namespace std;

class IDatabase
{
public:
	virtual void init() = 0;
	virtual int findUserByNamePass(const string& name, const string& pass) = 0;
	virtual string getAllCars() = 0;
	virtual bool carIsReserved(const string& id) = 0;
	virtual bool userIsRoot(const string& name) = 0;
	virtual void addCar(const string& carName) = 0;
};