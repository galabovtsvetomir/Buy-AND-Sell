#pragma once

#include "Field.h"

#include <ctype.h>

class PriceField : public Field<int> {
public:

	PriceField() : Field<int>("Price") {};

	virtual bool validate() {
		
		return true;
	}

	virtual void showError() {

		std::cout << "Invalid input!" << '\n';
	}

};