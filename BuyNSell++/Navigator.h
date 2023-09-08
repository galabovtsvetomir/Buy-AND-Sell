#pragma once
#include <string>
#include "AuthController.h"
#include "MenuController.h"
#include "ProductController.h"
#include "SearchController.h"
#include "SearchOptions.h"
#include "MyProductsOptions.h"
#include "Cart.h"
#include "BalanceOptions.h"

class Navigator
{
public:
	static void goTo(std::string path);
};

