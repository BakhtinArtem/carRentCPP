#pragma once
//	MESSAGE
const string OK_RESPONE = "OK";
const string ERROR_RESPONSE = "ERROR";
const string SUCCESSFUL_CONNECTION_RESPONSE = "You are successfully connected";
const string SUCCESSFUL_LOGIN_RESPONSE = "You are successfully logged in";
const string UNSUCCESSFUL_LOGIN_RESPONSE = "Name or password is not valid";
const string CAR_UNAVAILABLE = "Car is not available";

const char delimetr = ';';			//	delimetr used in request messages
const int USER_TABLE_ROW_SIZE = 3;	//	row number in user table
const string WHITESPACE = " ";
const string NEW_LINE = "\n";

//	REQEUSTS TYPES
const string REQUEST_LOGIN = "login";
const string REQUEST_NEW_USER = "newuser";
const string REQUEST_RESERVATION = "reserve";
const string REQUEST_CARS_LIST = "getcars";


const string RESERVE_OPTION = "Reserve a car";
const string RETURN_OPTION = "Return a car";
const string CLIENT_OPTIONS = "1." + WHITESPACE + RESERVE_OPTION + NEW_LINE + "2." + WHITESPACE + RETURN_OPTION;

