#pragma once

#include "User.h"
#include "Console.h"
#include "Navigator.h"
#include "App.h"
#include "AuthController.h"
#include <iostream>

class Options {
public:
	static void Show();
	static void ProcessInput();

private:
	void showGuestOptions();
	void showLoggedOptions();
	void ProcessGuestInput(int);
	void ProcessLoggedInput(int);
};