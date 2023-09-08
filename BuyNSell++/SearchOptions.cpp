#include "SearchOptions.h"


void SearchOptions::Handle()
{
	Console::clear();
	std::cout << '\n' << "YOUR OPTIONS ARE : " << std::endl << std::endl;
	std::cout << "1. View all products" << std::endl;
	// TO DO MORE SEARCH OPTIONS
	std::cout << "2. Go back" << std::endl;
	std::cout << "Your choice: ";
	int choice; std::cin >> choice;
	SearchOptions::ProcessSearchOptions(choice);
}

void SearchOptions::ProcessSearchOptions(int input)
{
	switch (input) {
	case 1:
		SearchOptions::HandleAllProducts();
		break;
		// TO DO MORE SEARCH OPTIONS
	case 2:
		Navigator::goTo("menu");
		break;
	default:
		App::setMessage("Invalid choice!");
		App::showMessage();
		Navigator::goTo("Show.Search.Options");
		break;
	}

}

void SearchOptions::HandleAllProducts()
{
	Console::clear();
	SearchController::getInstance().loadProducts();
	SearchController::getInstance().show_result();
	SearchOptions::afterSearchOptions();
}

void SearchOptions::afterSearchOptions()
{
	std::cout << '\n' << "YOUR OPTIONS ARE : " << std::endl << std::endl;
	std::cout << "1. Add product to your Cart" << std::endl;
	std::cout << "2. Go back " << std::endl;
	std::cout << "3. New Search" << std::endl;
	std::cout << "Your choice: ";
	int choice;
	std::cin >> choice;
	SearchOptions::ProcessAfterSearchOptions(choice);
}


void SearchOptions::ProcessAfterSearchOptions(int input)
{
	switch (input) {
	case 1:
		Navigator::goTo("add.product.cart");
		break;
	case 2:
		Navigator::goTo("menu");
		break;
	case 3:
		SearchOptions::Handle();
		break;
	default:
		App::setMessage("Invalid choice!");
		App::showMessage();
		SearchOptions::HandleAllProducts();
		break;
	}
}

