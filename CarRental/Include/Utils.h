#pragma once
//	MESSAGE
const string OK_RESPONE = "OK";
const string ERROR_RESPONSE = "ERROR";
const string SUCCESSFUL_CONNECTION_RESPONSE = "You are successfully connected";
const string SUCCESSFUL_LOGIN_RESPONSE = "You are successfully logged in";
const string UNSUCCESSFUL_LOGIN_RESPONSE = "Name or password is not valid";
const string CAR_UNAVAILABLE = "Car is not available";
const string USER_IS_ROOT_RESPONSE = "User is root";
const string TRUE_RESPONE = "true";
const string FALSE_RESPONSE = "false";

//	SYMBOLS
const char delimetr = ';';			//	delimetr used in request messages
const int USER_TABLE_ROW_SIZE = 3;	//	row number in user table
const string WHITESPACE = " ";
const string NEW_LINE = "\n";

//	REQEUSTS TYPES
const string REQUEST_LOGIN = "login";
const string REQUEST_NEW_USER = "newuser";
const string REQUEST_RESERVATION = "reserve";
const string REQUEST_CARS_LIST = "getcars";
const string REQUEST_LOGOUT = "logout";
const string REQUEST_USER_IS_ROOT = "root";
const string REQUEST_ADD_CAR = "addcar";
const string REQUEST_DELETE_CAR = "deletecar";

//	PERMISSION
const string ROOT_PERMISSION = "root";
const string USER_PERMISSION = "user";

// MENUs
const string RESERVE_OPTION = "Reserve a car";
const string RETURN_OPTION = "Return a car";
const string LOGOUT_OPTION = "Logout";
const string CLIENT_OPTIONS = \
	"1." + WHITESPACE + RESERVE_OPTION + NEW_LINE + \
	"2." + WHITESPACE + RETURN_OPTION + NEW_LINE + \
	"3." + WHITESPACE + LOGOUT_OPTION;

const string ADD_CAR_OPTION = "Add new car";
const string DELETE_CAR_OPTION = "Delete a car";
const string ROOT_OPTIONS = \
	"1." + WHITESPACE + ADD_CAR_OPTION + NEW_LINE + \
	"2." + WHITESPACE + DELETE_CAR_OPTION + NEW_LINE + \
	"3." + WHITESPACE + LOGOUT_OPTION;
