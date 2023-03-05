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
	cout << "Hello from db" << endl;
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
