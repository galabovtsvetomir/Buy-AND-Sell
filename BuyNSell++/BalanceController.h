#pragma once
#include "DB.h"
#include <exception>

class BalanceController {
public:
    BalanceController(BalanceController const&) = delete;
    void operator=(BalanceController const&) = delete;

    static BalanceController& getInstance()
    {
        static BalanceController instance;
        return instance;
    }
    //                              UserID
    static float getAvailableBalance(int);
    void TransferBuyerSeller(int, int, float);


protected:
    //                         buyerID, SellerID, Money
     
     void updateBalance(int, float);


private:
    BalanceController() = default;
};