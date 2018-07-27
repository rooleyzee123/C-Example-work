//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#include "ISAAccount.h"

//---------------------------------------------------------------------------
//ISAAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

ISAAccount::ISAAccount()
	: SavingsAccount(), currentYearlyDeposit_(0.0), maximumYearlyDeposit_(1000.0), endDepositPeriod_(15, 9, 2018)
{}
ISAAccount::~ISAAccount()
{}

////---------------------------------------------------------------------------
////user defined functions
////---------------------------------------------------------------------------
bool ISAAccount::canTransferIn(double amountToTransfer) const {
	bool canTransfer(false);
	if (creationDate_.currentDate() < endDepositPeriod_)
	{
		//check if the transfer doesnt go over the maximum yearly limit
		if (!((currentYearlyDeposit_ + amountToTransfer) > maximumYearlyDeposit_))
		{
			canTransfer = true;
		}
	}
	return canTransfer;
}
void ISAAccount::recordDeposit(double amountToDeposit) {
	if (creationDate_.currentDate() < endDepositPeriod_)
	{
		//check if the deposit doesnt go over the maximum yearly limit
		if (!((currentYearlyDeposit_ + amountToDeposit) > maximumYearlyDeposit_))
		{
			//create a deposit transaction
			Transaction aTransaction("deposit_to_ATM", amountToDeposit);
			//update active bankaccount
			transactions_.addNewTransaction(aTransaction);		//update transactions_
			updateBalance(amountToDeposit);			//increase balance_
			updateCurrentYearlyDeposit(amountToDeposit);
		}
	}
}
double ISAAccount::getMaximumYearlyDeposit() const {
	return maximumYearlyDeposit_;
}
double ISAAccount::getCurrentYearlyDeposit() const {
	return currentYearlyDeposit_;
}
Date ISAAccount::getEndDepositPeriod() const {
	return endDepositPeriod_;
}
bool ISAAccount::canDeposit(double amount) const {
	bool canDeposit(false);
	if (creationDate_.currentDate() < endDepositPeriod_)
	{
		//check if the transfer doesnt go over the maximum yearly limit
		if (!((currentYearlyDeposit_ + amount) > maximumYearlyDeposit_))
		{
			canDeposit = true;
		}
	}
	return canDeposit;
}

//private
void ISAAccount::updateCurrentYearlyDeposit(double a) {
	currentYearlyDeposit_ += a;
}