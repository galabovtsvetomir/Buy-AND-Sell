#pragma once
#include "MenuController.h"


void MenuController::handle()
{
	MenuController::showOptions();
	MenuController::processInput();
}

void MenuController::showOptions()
{
	Options::Show();
}


void MenuController::processInput()
{
	Options::ProcessInput();
}




