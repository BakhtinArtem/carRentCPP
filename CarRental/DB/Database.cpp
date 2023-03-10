#include "Database.h"
#include "../Include/Utils.h"

#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

//	use x64-debug version
const string USERS_FILE_PATH = "..\\..\\..\\DB\\Files\\users.txt";
const string USERS_ORDERS_PATH = "..\\..\\..\\DB\\Files\\orders.txt";
const string USERS_CARS_PATH = "..\\..\\..\\DB\\Files\\cars.txt";

void Database::init() {
	this->usersId = getCurrentIndex(USERS_FILE_PATH) + 1;
	this->orderId = getCurrentIndex(USERS_ORDERS_PATH) + 1;
	this->carsId = getCurrentIndex(USERS_CARS_PATH) + 1;
}

int Database::findUserByNamePass(const string& name, const string& pass)
{
	ifstream infile(USERS_FILE_PATH);
	if (!infile.good()) {
		cout << "File not found" << endl;
		return false;
	}
	
	string line, id, db_name, db_pass;
	while (getline(infile, line)) {
		stringstream streamLine(line);
		getline(streamLine, id, delimetr);			//	get id from db
		getline(streamLine, db_name, delimetr);		//	get name from db
		getline(streamLine, db_pass, delimetr);		//	get pass from db

		if (db_name == name && db_pass == pass) {
			return stoi(id);
		}
	}
	return -1;
}

string Database::getAllCars()
{
	ifstream infile(USERS_CARS_PATH);
	if (!infile.good()) {
		cout << "File not found" << endl;
		return "";
	}

	string line, id, name, all;
	while (getline(infile, line)) {
		stringstream streamLine(line);
		getline(streamLine, id, delimetr);			//	get id from db
		getline(streamLine, name, delimetr);		//	get name from db
		all += id + "-" + name + "\n";
	}
	return all;
}

bool Database::carIsReserved(const string& id)
{
	return existOrderWithCarId(id);
}

bool Database::existOrderWithCarId(const string& id)
{
	ifstream infile(USERS_ORDERS_PATH);
	if (!infile.good()) {
		cout << "File not found" << endl;
		return "";
	}

	string line, carId;
	while (getline(infile, line)) {
		stringstream streamLine(line);
		getline(streamLine, carId, delimetr);			//	get id from db
		if (carId == id) {
			return true;
		}
	}
	return false;
}

bool Database::userIsRoot(const string& name)
{
	ifstream infile(USERS_FILE_PATH);
	if (!infile.good()) {
		cout << "File not found" << endl;
		return "";
	}

	string line, id, db_name, pass, permission;
	while (getline(infile, line)) {
		stringstream streamLine(line);
		getline(streamLine, id, delimetr);
		getline(streamLine, db_name, delimetr);
		if (db_name != name) {
			continue;
		}
		getline(streamLine, pass, delimetr);
		getline(streamLine, permission, delimetr);
		//	check if user has root permission
		if (permission == ROOT_PERMISSION) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Database::addCar(const string& carName)
{
	fstream out(USERS_CARS_PATH, ios::app);
	out << to_string(this->carsId++) << delimetr << carName << endl;
	out.close();
}

int Database::getCurrentIndex(const string& filePath)
{
	//	get last index of orders
	ifstream in(filePath);
	string line, id = "0";
	while (getline(in, line)) {
		if (line == "") {
			continue;
		}
		stringstream ss(line);
		getline(ss, id, delimetr);
	}
	in.close();
	return stoi(id);
}
