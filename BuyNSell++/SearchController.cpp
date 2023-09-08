#include "SearchController.h"

 void SearchController::loadMyProduct()
{
	SearchController::getInstance().result.clear();

	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("Select [Ordery].[dbo].[Product].Product_id,[Ordery].[dbo].[Product].Product_name,"
		"[Ordery].[dbo].[Product].Category_id, [Ordery].[dbo].[Product].Price From[Ordery].[dbo].[Product] "
		"INNER JOIN[Ordery].[dbo].[product_saler] ON [Product].Product_id = [product_saler].product_id "
		"Where[product_saler].[user_id] = :1"));
	select.Param(1).setAsInt64() = stoi(User::get("User_id"));

	select.Execute();


	while (select.FetchNext()) {
		//                                      ProductID as key
		SearchController::getInstance().result[select.Field(1).asInt64()] = 
			Product(select.Field(2).asString().GetMultiByteChars(),
			select.Field(3).asInt64(),
			select.Field(4).asDouble(),
			0);
	}

	SearchController::update_quantities();
	return;
}

 void SearchController::loadProducts()
 {
	 SearchController::getInstance().result.clear();
	 SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("Select [Ordery].[dbo].[Product].Product_id,[Ordery].[dbo].[Product].Product_name,"
		"[Ordery].[dbo].[Product].Category_id, [Ordery].[dbo].[Product].Price From[Ordery].[dbo].[Product] "));

	select.Execute();

	while (select.FetchNext()) {
		//                                      ProductID as key
		SearchController::getInstance().result[select.Field(1).asInt64()] = 
			Product(select.Field(2).asString().GetMultiByteChars(),
			select.Field(3).asInt64(),
			select.Field(4).asDouble(),
			0);
	}
	SearchController::update_quantities();
 }

 void SearchController::update_quantities()
 {
	 for (auto it = SearchController::getInstance().result.begin();
		 it != SearchController::getInstance().result.end(); it++) {
		 (*it).second.set_quantity(ProductQuantity::get_Product_Quantity((*it).first));
	 }
 }

 void SearchController::show_result()
 {
	 bool haveResult = false;
	 int i = 1;
	 for (auto it = SearchController::getInstance().result.begin();
		 it != SearchController::getInstance().result.end(); it++) {
		 std::cout << '\n';
		 std::cout<<"index : " << i++<<'\n';
		 (*it).second.print();
		 haveResult = true;
	 }
	 if (!haveResult) std::cout << "You dont have Products to Show !" << '\n';
 }

 void SearchController::delete_product()
 {
	 int index;
	 do {
		 std::cout << "Please enter the product index, that you want to delete!" << '\n';
		 std::cout << "If you want to go back , enter - 0" << '\n';
		 std::cout << "index : ";
		  std::cin >> index;
		  if (index == 0) Navigator::goTo("My.listed.products") ;
	 } while (SearchController::getInstance().checkIndex(index));

	 if (index != 0) {
		 try {
			 Product::deleteProduct(SearchController::getInstance().get_productID(index));
			 App::setMessage("Successfully deleted Product !");
			 App::showMessage();
			 Navigator::goTo("menu");
		 }
		 catch(std::exception exception) {
			 App::setMessage(exception.what());
			 App::showMessage();
			 Navigator::goTo("menu");
		 }
	 }
	 else return;
	
 }

 Product SearchController::get_product(int ProductID)
 {
	 return SearchController::getInstance().result[ProductID];
 }

 int SearchController::get_productID(int index)
 {
	 auto it = SearchController::getInstance().result.begin();
	 int count = 1;

	 while (count<index) {
		 it++;
		 count++;
	 }

	 return (*it).first;
	 
 }

 bool SearchController::checkIndex(int index)
 {
	 if (index > SearchController::getInstance().result.size() or index < 1) return true;
	 else return false;
 }
