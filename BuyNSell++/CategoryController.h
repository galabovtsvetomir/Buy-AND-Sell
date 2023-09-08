#pragma once
#include "DB.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
class Category {

public:
	void print_list();

	Category() {
		SAConnection& con = DB::conn();
		SACommand select(&con);

		select.setCommandText(_TSA("SELECT * FROM [Ordery].[dbo].[Categorises]"));
		select.Execute();

		while (select.FetchNext()) {
		list[ select.Field(_TSA("category_id")).asInt64()]=
				 select.Field(_TSA("category_name")).asString().GetMultiByteChars() ;
		}
	}


private:
	//           category_id  , category_name
	std::unordered_map<int,std::string>   list;

};