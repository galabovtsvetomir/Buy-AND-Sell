#pragma once

#include "ProductController.h"
#include "ProductQuantity.h"
#include "Navigator.h"
#include <unordered_map>

class SearchController {
public:
	SearchController(SearchController const&) = delete;
	void operator=(SearchController const&) = delete;

	static SearchController& getInstance()
	{
		static SearchController instance;
		return instance;
	}
	static void loadMyProduct();
	static void loadProducts();
	static void update_quantities();
	static void show_result();
	static void delete_product();
	static Product get_product(int);
    static int get_productID(int);
	static bool checkIndex(int);

	
private:
	//           Product_id ,Product
	std::unordered_map<int, Product> result;

	SearchController()=default;
	

};