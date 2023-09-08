#pragma once

#include "UserModel.h"
#include <string>




class AuthController
{
public:
	static void handleSignUp();

	static void handleSignIn();

	static void Logout();

	UserModel* user;


	AuthController() : user(new UserModel) { }

	AuthController(const AuthController& other)
	{
		copy(other);
	}

	AuthController& operator=(const AuthController& other)
	{
		if (this != &other) {
			erase();
			copy(other);
		}

		return *this;
	}

	~AuthController()
	{
		delete user;
	}

	

protected:

	bool signIn() const;
	bool signUp() const;
	void promptSignInInput();
	void promptSignUpInput();

	void copy(const AuthController& other)
	{
		user = other.user;
	}

	void erase()
	{
		delete user;
	}
};
