#include "ProductController.h"
#include "CategoryController.h"

#include "ProductNameField.h"
#include "CategoryField.h"
#include "PriceField.h"
#include "QuantityField.h"
#include "App.h"
#include "Navigator.h"

#include <exception>
void Product::addProduct()
{
	Product product;
	product.promptAddInput();
	try {
		product.insertToDb();
		product.attachToSaler();
		product.addQuantity();
		App::setMessage("Successfully listed product.");
		App::showMessage();
		Navigator::goTo("menu");
	}
	catch (std::exception exception) {
		App::setMessage(exception.what());
		App::showMessage();
		Navigator::goTo("menu");
	}
}

int Product::Find_ProductID(std::string Product_name)
{
	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("SELECT * FROM [Ordery].[dbo].[Product]"
		"WHERE [Product_name] = :1 "));
	select << _TSA(Product_name.c_str());
	select.Execute();

	                        //this is the ProductID with that ProductName; 
	if (select.FetchNext()) return select.Field(1).asInt64();
	else return -1;//didnt find any Product_id with that Product Name 
}

void Product::insertToDb()
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA("INSERT INTO [Ordery].[dbo].[Product] (Category_id, Product_name, Price)"
		"VALUES (:1, :2, :3)"));
	insert.Param(1).setAsInt64() = category_ID;
	insert.Param(2).setAsString() = _TSA(productName.c_str());
	insert.Param(3).setAsInt64()=price;

	insert.Execute();

	if (insert.RowsAffected() == 0) {
		throw std::exception("Unable to list Product !");
	}
}

void Product::promptAddInput()
{
	this->productName = ProductNameField().prompt();
	Category available;
	available.print_list();
	this->category_ID = CategoryField().prompt();
	this->price = PriceField().prompt();
	this->quantity = QuantityField().prompt();
}

void Product::attachToSaler()
{
	ProductSaler productsaler(Product::Find_ProductID(this->productName),(stoi(User::get("User_id"))));
	productsaler.addToDB();
}

void Product::addQuantity()
{
	ProductQuantity productquantity(Product::Find_ProductID(this->productName), this->quantity);
	productquantity.addToDB();
}

void Product::set_quantity(int quantity)
{
	this->quantity = quantity;
}

float Product::get_price()
{
	return this->price;
}

int Product::get_quantity()
{
	return this->quantity;
}

void Product::deleteProduct(int ProductID)
{
	SAConnection& con = DB::conn();
	SACommand deleteCommand(&con);

	deleteCommand.setCommandText(_TSA("DELETE FROM [Ordery].[dbo].[Product] WHERE [Product_id] = :1"));
	deleteCommand.Param(1).setAsLong() = ProductID;

	deleteCommand.Execute();

	if (deleteCommand.RowsAffected() == 0) {
		throw std::exception("Unable to demove song from playlist");
	}
}

void Product::print()
{
	std::cout << "Product name :" << this->productName << '\n';
	std::cout << "Category :" << this->category_ID << '\n';
	std::cout << "Price :" << this->price << '\n';
	std::cout << "Quantity:" << this->quantity << '\n';
}

