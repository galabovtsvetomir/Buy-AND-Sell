#pragma once

#include <string>
#include <SQLAPI.h>

#include "DB.h"

using std::string;

class UserModel
{
public:
	string email;
	string username;
	string password;
	string passwordConfirmation;

	UserModel() : email(""), username(""), password(""), passwordConfirmation("") { }

	//Checks if this username exists in the DB
	static bool exists(string name)
	{
		SAConnection& con = DB::conn();
		SACommand select(&con);

		select.setCommandText(_TSA("SELECT * FROM [Ordery].[dbo].[User] WHERE [username] = :1"));
		select << _TSA(name.c_str());
		select.Execute();

		return select.FetchNext();
	}
//inserting user to the DB
	int insert()
	{
		SAConnection& con = DB::conn();
		SACommand insert(&con);

		insert.setCommandText(_TSA("INSERT INTO [Ordery].[dbo].[User] (username, password, email) VALUES (:1, :2, :3)"));
		insert << _TSA(username.c_str()) << _TSA(password.c_str()) << _TSA(email.c_str());
		insert.Execute();

		return insert.RowsAffected();
	}
};

