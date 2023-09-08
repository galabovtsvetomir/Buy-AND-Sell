#pragma once
#include "DB.h"
#include "exception"

class ProductSaler {
public:
	ProductSaler(int ProductID, int UserID) :ProductID(ProductID), UserID(UserID) {};
	static int getProductSalerID(int);
	void addToDB();
private:
	int ProductID;
	int UserID;
};