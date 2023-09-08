#include "OrderProduct.h"

void OrderProduct::addToDB(int OrderID, int ProductID, int quantity)
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA(
		"INSERT INTO [Ordery].[dbo].[order_product] (order_id, product_id, quantity)"
		"VALUES (:1, :2, :3)"
	));
	insert.Param(1).setAsInt64() = OrderID;
	insert.Param(2).setAsInt64() = ProductID;
	insert.Param(3).setAsDouble() = quantity;

	insert.Execute();

	if (insert.RowsAffected() == 0) {
		throw std::exception("Unable to insert Order_Product !");
	}
}
