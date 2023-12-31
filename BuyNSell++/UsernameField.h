#pragma once

#include <string>
#include <iostream>

#include "Field.h"
#include "UserModel.h"

using std::string;
using std::cout;
using std::endl;

class UsernameField : public Field<string>
{
public:
	 static const int MIN_LENGTH = 6;
	 static const int MAX_LENGTH = 25;

	UsernameField() : Field<string>("Username") {}

	void showError()
	{
		cout << "Username must be unique and between " << MIN_LENGTH <<
			" and " << MAX_LENGTH << " characters long." << endl;
	}

	bool validate()
	{
		return value.length() >= MIN_LENGTH &&
			value.length() <= MAX_LENGTH &&
			!UserModel::exists(value);
	}
};
