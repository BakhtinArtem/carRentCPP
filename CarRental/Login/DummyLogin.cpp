#include "Login.h"
#include <iostream>

using namespace std;

void Login::init() {
	cout << "Hi from login" << endl;
}

void Login::userExist(IDatabase& db)
{
	cout << "USER EXIST 4REAL";
}
