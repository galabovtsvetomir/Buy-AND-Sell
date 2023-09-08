#include "ProductQuantity.h"

void ProductQuantity::addToDB()
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA("INSERT INTO [Ordery].[dbo].[Product_quantity] (Product_id, quantity)"
		"VALUES (:1, :2)"));
	insert.Param(1).setAsInt64() = this->ProductID;
	insert.Param(2).setAsInt64() = this->quantity;

	insert.Execute();

	if (insert.RowsAffected() == 0) {
		throw std::exception("Unable to add the product quantity !");
	}
}

int ProductQuantity::get_Product_Quantity(int productID)
{
	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("SELECT * FROM [Ordery].[dbo].[Product_quantity]"
		"WHERE [Product_id] = :1 "));
	select.Param(1).setAsInt64() = productID;

	select.Execute();


	if (select.FetchNext()) return select.Field(3).asInt64();
	else return -1;
}

bool ProductQuantity::checkIfQuantityAvailable(int productID, int quantity)
{
	if (quantity > ProductQuantity::get_Product_Quantity(productID)) return true;
	else return false;
}

void ProductQuantity::UpdateQuantityInDB(int ProductID, int orderQuantity)
{
	SAConnection& con = DB::conn();
	SACommand update(&con);

	int newquantity = ProductQuantity::get_Product_Quantity(ProductID) - orderQuantity;

	update.setCommandText(_TSA("UPDATE [Ordery].[dbo].[Product_quantity]"
		"SET [Ordery].[dbo].[Product_quantity].quantity= :1 "
		"WHERE [Product_id] = :2 "));
	update.Param(1).setAsInt64() = newquantity;
	update.Param(2).setAsInt64() = ProductID;

	update.Execute();

	if (update.RowsAffected() == 0) throw std::exception("Unable to update quantity in ProductQuantity !");

}
