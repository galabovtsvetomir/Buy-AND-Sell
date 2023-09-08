#pragma once
#include "SearchController.h"
#include "Navigator.h"
#include "App.h"

class SearchOptions {

public:
	static void Handle();
	static void ProcessSearchOptions(int);
	static void HandleAllProducts();
	
	static void afterSearchOptions();
	static void ProcessAfterSearchOptions(int);

private:
};