#include "Options.h"



void Options::Show()
{
	Options instance;
	if (User::isLoggedIn()) instance.showLoggedOptions();
	else instance.showGuestOptions();
}

void Options::ProcessInput()
{
	int input; Options instance;
	std::cin >> input;
	if (User::isLoggedIn())  instance.ProcessLoggedInput(input);
	else instance.ProcessGuestInput(input);
}

void Options::showGuestOptions()
{
	Console::clear();
	std::cout << "Welcome to Buy & Sell " << std::endl << std::endl;

	std::cout << "1. Login" << std::endl;
	std::cout << "2. Create an account" << std::endl;
	std::cout << std::endl;
	std::cout << "0. Exit" << std::endl;
	std::cout << std::endl;
	std::cout << "Your choice: ";
}

void Options::showLoggedOptions()
{
	Console::clear();
	std::cout << "Welcome to Buy & Sell, " << User::get("username") << std::endl << std::endl;

	std::cout << "1. List Product for sale" << std::endl;
	std::cout << "2. View my listed products" << std::endl;
	std::cout << "3. View available products" << std::endl;
	std::cout << "4. View my Cart" << std::endl;
	std::cout << "5. Your Balance" << std::endl;
	std::cout << "6. Logout" << std::endl;
	std::cout << std::endl;
	std::cout << "0. Exit" << std::endl;
	std::cout << std::endl;
	std::cout << "Your choice: ";
}

void Options::ProcessGuestInput(int input)
{
	switch (input) {
	case 0:
		break;
	case 1:
		Navigator::goTo("menu.signIn");
		break;
	case 2:
		Navigator::goTo("menu.signUp");
		break;
	default:
		App::setMessage("Invalid choice!");
		App::showMessage();
		Navigator::goTo("menu");
		break;
	}
}

void Options::ProcessLoggedInput(int input)
{
	switch (input) {
	case 0:
		break;
	case 1:
		Navigator::goTo("List.Product");
		break;
	case 2:
		Navigator::goTo("My.listed.products");
		break;
	case 3:
		Navigator::goTo("Show.Search.Options");
		break;
	case 4:
		Navigator::goTo("show.cart.products");
		break;
	case 5:
		Navigator::goTo("balance.options");
		break;
	case 6:
		AuthController::Logout();
		Navigator::goTo("menu");
		break;
	default:
		App::setMessage("Invalid choice!");
		App::showMessage();
		Navigator::goTo("menu");
		break;
	}

}
