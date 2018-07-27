//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#include "ChildAccount.h"

//---------------------------------------------------------------------------
//ChildAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

ChildAccount::ChildAccount()
: SavingsAccount(), maximumPaidIn_(100.0), minimumPaidIn_(10.0)
{}
ChildAccount::~ChildAccount()
{}

////---------------------------------------------------------------------------
////user defined functions
////---------------------------------------------------------------------------
void ChildAccount::recordDeposit(double amountToDeposit) {
	//check if amountToDeposit is between the minimumPaidIn and maximumPaidIn
	if (amountToDeposit >= minimumPaidIn_ && amountToDeposit <= maximumPaidIn_)
	{
		//create a deposit transaction
		Transaction aTransaction("deposit_to_ATM", amountToDeposit);
		//update active bankaccount
		transactions_.addNewTransaction(aTransaction);		//update transactions_
		updateBalance(amountToDeposit);			//increase balance_
	}
}
bool ChildAccount::canWithdraw(double amountToWithdraw) const {
	//return false, as you cannot withdraw from a child account (until you are an adult which is not covered)
	return false;
}
bool ChildAccount::canTransferOut(double amountToTransfer) const {
	return false;
}
bool ChildAccount::canTransferIn(double amountToTransfer) const {
	return ((amountToTransfer > minimumPaidIn_) && (amountToTransfer < maximumPaidIn_));
}
double ChildAccount::getMaximumPaidIn() const {
	return maximumPaidIn_;
}
double ChildAccount::getMinimumPaidIn() const {
	return minimumPaidIn_;
}
bool ChildAccount::canDeposit(double amount) const {
	return (amount <= getMaximumPaidIn() && amount >= getMinimumPaidIn());
}