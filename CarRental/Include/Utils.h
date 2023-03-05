#pragma once

//	MESSAGE
const string SUCCESSFUL_CONNECTION = "You are successfully connected";

const char delimetr = ';';			//	delimetr used in request messages
const int USER_TABLE_ROW_SIZE = 3;	//	row number in user table

const string REQUEST_LOGIN = "login";
const string REQUEST_NEW_USER = "newuser";

const enum REQUEST_TYPE {			//	request types
	LOGIN
};