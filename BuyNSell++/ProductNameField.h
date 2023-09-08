#pragma once
#include "Field.h"
#include <string>

class ProductNameField : public Field<string>
{
public:
	static const int MIN_LENGTH = 6;
	static const int MAX_LENGTH = 25;

	ProductNameField() : Field<string>("Product Name") {}

	void showError()
	{
		cout << "Product name be UNIQUE and  between " << MIN_LENGTH <<
			" and " << MAX_LENGTH << " characters long." << '\n';
	}

	bool validate()
	{
		return !exist(value);	   
	}
	
	bool exist(string value) {
		SAConnection& con = DB::conn();
		SACommand select(&con);

		select.setCommandText(_TSA("SELECT * FROM [Ordery].[dbo].[Product]"
			"WHERE [Ordery].[dbo].[Product].[Product_name] = :1"));
		select << _TSA(value.c_str());
		select.Execute();

		return select.FetchNext();
	}
};
