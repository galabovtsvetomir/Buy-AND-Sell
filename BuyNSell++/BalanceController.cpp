#include "BalanceController.h"



float BalanceController::getAvailableBalance(int UserID)
{
	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("SELECT * FROM [Ordery].[dbo].[user_balance]"
		"WHERE [user_id] = :1 "));
	select.Param(1).setAsInt64() = UserID;

	select.Execute();

	
	if (select.FetchNext()) return select.Field(2).asDouble();
	else return 0;//didnt find
}

void BalanceController::TransferBuyerSeller(int BuyerID, int SellerID, float money)
{
	float BuyerNewBalance = BalanceController::getAvailableBalance(BuyerID) - money;
	float SellerNewBalance = BalanceController::getAvailableBalance(SellerID) + money;
	BalanceController& BC = BalanceController::getInstance();
	BC.updateBalance(BuyerID, BuyerNewBalance);
	BC.updateBalance(SellerID, SellerNewBalance);
}

void BalanceController::updateBalance(int UserID, float money)
{

	SAConnection& con = DB::conn();
	SACommand update(&con);

	update.setCommandText(_TSA("UPDATE [Ordery].[dbo].[user_balance]"
		"SET [Ordery].[dbo].[user_balance].balance= :1 "
		"WHERE [user_id] = :2 "));
	update.Param(1).setAsDouble() = money;
	update.Param(2).setAsInt64() = UserID;

	update.Execute();

	if (update.RowsAffected() == 0) throw std::exception("Unable to update Balance  !");
}


