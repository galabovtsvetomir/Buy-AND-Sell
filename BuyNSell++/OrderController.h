#pragma once
#include "Cart.h"
#include "ProductSaler.h"
#include "User.h"
#include "OrderProduct.h"
#include "ProductQuantity.h"

class OrderController {
public:
    OrderController(OrderController const&) = delete;
    void operator=(OrderController const&) = delete;

    static OrderController& getInstance()
    {
        static OrderController instance;
        return instance;
    }

	static void HandleOrder();

protected:

    int InsertDB(int, int, double);

private:
    OrderController() = default;
};
