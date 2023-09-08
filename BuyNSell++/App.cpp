#include "App.h"

void App::setMessage(std::string message)
{
	App::getInstance().message = message;
}

void App::showMessage()
{
	App& app = App::getInstance();

	if (app.message != "") {
		std::cout << App::getInstance().message << std::endl << std::endl;
		app.message = "";
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}