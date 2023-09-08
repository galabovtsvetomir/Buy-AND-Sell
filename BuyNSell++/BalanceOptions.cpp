#include "BalanceOptions.h"

void BalanceOptions::HandleBalance()
{
	Console::clear();
	std::cout << '\n' << "YOUR OPTIONS ARE : " << std::endl << std::endl;
	std::cout << "1. View your Balance" << std::endl;
	std::cout << "2. Add Money " << std::endl;
	std::cout << "3. Go back" << std::endl;
	std::cout << "Your choice: ";
	int choice; std::cin >> choice;
	BalanceOptions::ProccessBalanceOptions(choice);
}

void BalanceOptions::ProccessBalanceOptions(int input)
{
	switch (input) {
	case 1:
		Console::clear();
		std::cout << User::getInstance().get("username") << ", your balance is :";
		App::setMessage(std::to_string(BalanceController::getInstance().getAvailableBalance(stoi(User::getInstance().get("User_id")))));
		App::showMessage();
		Navigator::goTo("balance.options");
		break;
	
	case 2:
		Navigator::goTo("menu");
		break;
	case 3:
		Navigator::goTo("menu");
		break;
	default:
		App::setMessage("Invalid choice!");
		App::showMessage();
		Navigator::goTo("balance.options");
		break;
	}

}

