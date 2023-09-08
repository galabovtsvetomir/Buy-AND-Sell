#include "AuthController.h"
#include "DB.h"
#include <exception>
#include <iostream>
#include <regex>

#include "UsernameField.h"
#include "PasswordField.h"
#include "Email.h"
#include "PasswordComformation.h"

#include "User.h"
#include "Navigator.h"
#include "App.h"


using std::exception;
using namespace std;



void AuthController::handleSignIn() {
	AuthController authcontroller;
	authcontroller.promptSignInInput();

	try {
		if (authcontroller.signIn()) App::setMessage("Successfully,Logged!");
		else App::setMessage("Login failed!");
		App::showMessage();

		Navigator::goTo("menu");
	}
	catch (exception exception) {
		App::setMessage(exception.what());
		App::showMessage();
	}

}

void AuthController::Logout()
{
	User::logout();
}

void AuthController::promptSignInInput()
{
	this->user->username = UsernameField().simplePrompt();
	this->user->password = PasswordField().simplePrompt();
}

void AuthController::promptSignUpInput()
{//                                    prompt with validation
	this->user->username = UsernameField().prompt();
	this->user->password = PasswordField().prompt();
	this->user->email = EmailField().prompt();
	this->user->passwordConfirmation = PasswordConfirmationField(this->user->password).prompt();
}


bool AuthController::signIn() const
{
	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("SELECT * FROM [Ordery].[dbo].[User] WHERE [username] = :1 AND [password] = :2"));
	select << _TSA(user->username.c_str()) << _TSA(user->password.c_str());
	select.Execute();

	//user found, so we login
	if (select.FetchNext()) {
		User::getInstance().login(select);
		return true;
	}
	//user not found
	else {
		return false;
	}
}

bool AuthController::signUp() const {
	//inserting user attached to this authcontroller to the DB
	if (this->user->insert() > 0) return true;
	else return false;
}


void AuthController::handleSignUp(){
	AuthController authcontroller;
	authcontroller.promptSignUpInput();

	try {
		if(authcontroller.signUp()) App::setMessage("Successfully, Registered!");
		else App::setMessage("Registration failed!");
		App::showMessage();

		Navigator::goTo("menu");
	}
	catch (exception exception) {
		App::setMessage(exception.what());
		App::showMessage();
	}
}
