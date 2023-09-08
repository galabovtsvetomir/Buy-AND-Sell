#include "Cart.h"

void Cart::addProduct(int ProductID,int quantity)
{
	Cart::getInstance().cart_products[ProductID] = SearchController::getInstance().get_product(ProductID);
	Cart::getInstance().cart_products[ProductID].set_quantity(quantity);
}

void Cart::PrintContent()
{
	bool haveResult = false;
	int i = 1;
	for (auto it = Cart::getInstance().cart_products.begin();
		it != Cart::getInstance().cart_products.end(); it++) {
		std::cout << '\n';
		std::cout << "index : " << i++ << '\n';
		(*it).second.print();
		haveResult = true;
	}
	if (!haveResult) std::cout << "You dont have Products to Show !" << '\n';
}
void Cart::HandleADD()
{
	int index; int quantity;
	do {
		std::cout << '\n';
		std::cout << "Please enter the Product index you want to add !" << '\n';
		std::cout << "index : ";
	    std::cin >> index;
	} while (SearchController::getInstance().checkIndex(index));
	
	do {
		std::cout << "Please enter the quantity that you want !" << '\n';
		std::cout << "quantity : ";
		std::cin >> quantity;
	} while (ProductQuantity::checkIfQuantityAvailable(SearchController::getInstance().get_productID(index),quantity)
		or quantity < 1);
     
	//Check if the product is not listed by the same user
	if (stoi(User::getInstance().get("User_id")) != 
		ProductSaler::getProductSalerID(SearchController::getInstance().get_productID(index))) {
		//and if it is not already added to the cart
		if (Cart::getInstance().cart_products.count(SearchController::getInstance().get_productID(index))==0) {
			Cart::addProduct(SearchController::getInstance().get_productID(index), quantity);
				App::setMessage("Successfully added to Cart!");
				App::showMessage();
	    }
		else {
			App::setMessage("Sorry, You already added it to you CART!");
			App::showMessage();
		}
	}

	else {
		App::setMessage("Sorry,you cant add your own products !");
		App::showMessage();
	}
	
}

void Cart::Handle()
{
	Console::clear();
	Cart::PrintContent();
	std::cout << '\n' << "YOUR OPTIONS ARE : " << std::endl << std::endl;
	std::cout << "1. Remove product" << std::endl;
	std::cout << "2. Pay and Order" << std::endl;
	std::cout << "3. Go back " << std::endl;
	
	std::cout << "Your choice: ";
	int choice;
	std::cin >> choice;
	Cart::ProcessInput(choice);
}

void Cart::ProcessInput(int input)
{
	switch (input) {
	case 1:
		Cart::HandleRemove();
		App::setMessage("Successfully removed product from Cart!");
		App::showMessage();
		Navigator::goTo("menu");
		break;
		
	case 2:
		Cart::HandlePay();
		break;
	case 3:
		Navigator::goTo("menu");
		break;
	default:
		App::setMessage("Invalid choice!");
		App::showMessage();
		Navigator::goTo("Show.Search.Options");
		break;
	}

}

void Cart::HandleRemove()
{
	int index; 
	do {
		std::cout << '\n';
		std::cout << "Please enter the Product index you want to remove !" << '\n';
		std::cout << "index : ";
		std::cin >> index;
	} while (index>Cart::getInstance().cart_products.size() 
		or index < 1);

	Cart::RemoveProduct(index);

}

void Cart::RemoveProduct(int indx)
{
	auto it = Cart::getInstance().cart_products.begin();
	for (int i = 1; i < indx; i++) {
		it++;
	}

	Cart::getInstance().cart_products.erase(it);
}

int Cart::calculate_price()
{
	double price = 0;
	for (auto it = Cart::getInstance().cart_products.begin();
		it != Cart::getInstance().cart_products.end(); it++) {
		price += (*it).second.get_price() * (*it).second.get_quantity();
	}
	return price;
}

void Cart::HandlePay()
{
	std::cout << '\n';
	std::cout << "Are you sure you want to pay - ";
	std::cout << Cart::calculate_price() << '\n';
	std::cout << "Press '1' to continue " << '\n';
	std::cout << "Press '0' to go back." << '\n';
	std::cout << "Your choice:";
	int choice; std::cin >> choice;
	switch (choice) {
	case 1:
		
		if (Cart::PayCheck()) OrderController::HandleOrder();
		else Navigator::goTo("show.cart.products");
		
		break;

	case 0:
		Navigator::goTo("show.cart.products");
		break;
	
	default:
		App::setMessage("Invalid choice!");
		App::showMessage();
		Navigator::goTo("show.cart.products");
		break;
	}
}

bool Cart::PayCheck()
{
	float UserBalance = BalanceController::getAvailableBalance(stoi(User::get("User_id")));

	if (UserBalance < Cart::calculate_price()) {
		App::setMessage("Sorry, you dont have enough Money :(");
		App::showMessage();
		return false;
	}
	else return true;
}

