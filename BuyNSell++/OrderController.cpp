#include "OrderController.h"

void OrderController::HandleOrder()
{
	//get products from Cart
	for (auto it = Cart::getInstance().cart_products.begin();
		it != Cart::getInstance().cart_products.end(); it++) {
		int SellerID = ProductSaler::getProductSalerID((*it).first);
		int BuyerID = stoi(User::get("User_id"));
		double Price = ((*it).second.get_price() * (*it).second.get_quantity());
		try {
			//Create Order
			int OrderID = OrderController::getInstance().InsertDB(SellerID, BuyerID, Price);
			//Attach to the Order to the Product 
			OrderProduct::addToDB(OrderID, (*it).first, (*it).second.get_quantity());
			//Update available quantity in Products
			ProductQuantity::UpdateQuantityInDB((*it).first, (*it).second.get_quantity());
			//Transfer the money 
			BalanceController::getInstance().TransferBuyerSeller(BuyerID, SellerID, Price);
		}
		catch (std::exception exception) {
			App::setMessage(exception.what());
			App::showMessage();
			Navigator::goTo("menu");
		}
	}
}



int OrderController::InsertDB(int SellerID, int BuyerID, double price)
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA(
		"INSERT INTO [Ordery].[dbo].[Order] (saler_id, buyer_id, price)"
		"VALUES (:1, :2, :3)"
		"SELECT @@IDENTITY"
	));
	insert.Param(1).setAsInt64() = SellerID;
	insert.Param(2).setAsInt64() = BuyerID;
	insert.Param(3).setAsDouble() = price;

	insert.Execute();

	if (insert.FetchNext()) return insert.Field(1).asInt64();
	else throw::std::exception("Error occured adding to OrderDB");
}




