#pragma once
#include <string>
#include<iostream>
#include <thread>
#include <chrono>

class App
{
public:
	App(App const&) = delete;
	void operator=(App const&) = delete;

	static App& getInstance() {
		static App instance;
		return instance;
	}
	static void setMessage(std::string message);
	static void showMessage();

private:

	std::string message;
	App() { }
};
