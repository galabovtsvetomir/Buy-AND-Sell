#include "ProductSaler.h"

int ProductSaler::getProductSalerID(int productID)
{
	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("Select* From [Ordery].[dbo].[product_saler] "
		"Where [Ordery].[dbo].[product_saler].product_id = :1"));
	select.Param(1).setAsInt64() = productID;
	
	select.Execute();

	if (select.FetchNext()) return select.Field(2).asInt64();
	else return -1;
}

void ProductSaler::addToDB()
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA("INSERT INTO [Ordery].[dbo].[product_saler] (user_id, product_id)"
		"VALUES (:1, :2)"));
	insert.Param(1).setAsInt64() = this->UserID;
	insert.Param(2).setAsInt64() = this->ProductID;
	
	insert.Execute();

	if (insert.RowsAffected() == 0) {
		throw std::exception("Unable to attach to Saler !");
	}
}
