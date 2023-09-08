#pragma once
#include "Controller.h"
#include <string>
#include <iostream>
#include "ProductSaler.h"
#include "ProductQuantity.h"
#include "User.h"

class Product : public Controller
{
public:
	static void addProduct();
	static int Find_ProductID(std::string);
	static void deleteProduct(int);
	void print();

	void set_quantity(int);
	float get_price();
	int get_quantity();

	
Product() : productName(""), category_ID(-1), price(-1), quantity(-1) {};
Product(std::string productName, int category_ID, float price, int quantity)
	: productName(productName), category_ID(category_ID), price(price), quantity(quantity) {};

protected:
	std::string productName;
	int category_ID;
	float price;
	int quantity;


	void insertToDb();
	void promptAddInput();
	void attachToSaler();
	void addQuantity();
	
	
};
	

