#include "MyProductsOptions.h"

void MyProductsOptions::HandleMyProducts()
{
	SearchController::getInstance().loadMyProduct();
	SearchController::getInstance().show_result();
	std::cout << '\n' << "YOUR OPTIONS ARE : " << std::endl << std::endl;
	std::cout << "1. Delete Product" << std::endl;
	std::cout << "2. Go back" << std::endl;
	std::cout << "Your choice: ";
	int choice;
	std::cin >> choice;
	MyProductsOptions::ProcessMyProductsInput(choice);
}

void MyProductsOptions::ProcessMyProductsInput(int input)
{
	switch (input) {
	case 1:
		Navigator::goTo("delete.MyProduct");
		break;
	case 2:
		Navigator::goTo("menu");
		break;
	default:
		App::setMessage("Invalid choice!");
		App::showMessage();
		Navigator::goTo("My.listed.products");
		break;
	}
}