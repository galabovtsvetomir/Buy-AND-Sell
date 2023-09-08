#pragma once

#include "Field.h"



class QuantityField : public Field<int> {
public:

	QuantityField() : Field<int>("Quantity") {};

	virtual bool validate() {

		return true;
	}

	virtual void showError() {

		std::cout << "Invalid input!" << '\n';
	}

};