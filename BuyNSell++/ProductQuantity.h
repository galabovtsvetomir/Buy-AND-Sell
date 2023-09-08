#pragma once
#include "DB.h"
#include <exception>

class ProductQuantity {
public:
	ProductQuantity(int ProductID, int quantity) :ProductID(ProductID), quantity(quantity) {};
	void addToDB();
	static int get_Product_Quantity(int productID);
	static bool checkIfQuantityAvailable(int productID, int quantity);
	static void UpdateQuantityInDB(int ProductID, int orderQuantity);
private:
	int ProductID;
	int quantity;
	
};