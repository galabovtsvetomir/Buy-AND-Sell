#pragma once

#include "Field.h"
#include "DB.h"

class CategoryField :public Field<int> {
public:
	CategoryField() :Field<int>("Category id") {};

	//checks if such category_id exists in the DB
	bool validate() {

		SAConnection& con = DB::conn();

		SACommand* select = new SACommand(&con);

		(*select).setCommandText(_TSA(
			"SELECT * FROM [Ordery].[dbo].[Categorises] "

			"WHERE [Ordery].[dbo].[Categorises].[category_id] = :1 "

		));

		(*select).Param(1).setAsLong() = value;
		(*select).Execute();

		if ((*select).FetchNext()) return true;
		else return false;
	}

	void showError() {
		std::cout << "No such Category exist!"<<"\n";
	}

};
