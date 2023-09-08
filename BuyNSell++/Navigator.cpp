#pragma once
#include "Navigator.h"


void Navigator::goTo(std::string path) {
	//MAIN MENU
	if (path == "menu") {
		MenuController::handle();
	}
	//LOGIN
	if (path == "menu.signIn") {
		AuthController::handleSignIn();
	}
	//REGISTRATION
	if (path == "menu.signUp") {
		AuthController::handleSignUp();
	}
    //ADD PRODUCT 
	if (path == "List.Product") {
		Product::addProduct();
	}
	//My listed Product
	if (path == "My.listed.products") {
		Console::clear();
		MyProductsOptions::HandleMyProducts();
	}
	//Delete From my listed products
	if (path == "delete.MyProduct") {
		SearchController::delete_product();
	}
	//Show Search Options
	if (path == "Show.Search.Options") {
		SearchOptions::Handle();
	}
	//HANDLE ADD
	if (path == "add.product.cart") {
		Cart::HandleADD();
		Navigator::goTo("Show.Search.Options");
	}
	//SHOW MY CART PRODUCTS
	if (path == "show.cart.products")
    {
		Cart::Handle();
	}
	//HANDLE BALANCE INTERFACE
	if (path == "balance.options") {
		BalanceOptions::HandleBalance();
	}

}