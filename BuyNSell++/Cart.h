#pragma once
#include <unordered_map>
#include "ProductController.h"
#include "SearchController.h"
#include "BalanceController.h"
#include "OrderController.h"

class Cart {
public:

    Cart(Cart const&) = delete;
    void operator=(Cart const&) = delete;

    static Cart& getInstance()
    {
        static Cart instance;
        return instance;
    } 
    
    static void Handle();

    static void HandleADD();
    static void addProduct(int ,int);
    static void PrintContent();
   
    static void HandleRemove();
    static void ProcessInput(int);
    static void RemoveProduct(int);

    static int calculate_price();

    static void HandlePay();
    static  bool PayCheck();

    //          productID, Product
    std::unordered_map<int, Product> cart_products;
private:
    Cart() = default;
};