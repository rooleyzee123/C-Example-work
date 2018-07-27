//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#include "SavingsAccount.h"

//---------------------------------------------------------------------------
//SavingsAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

SavingsAccount::SavingsAccount()
	: BankAccount(), minimumBalance_(50)
{}
SavingsAccount::~SavingsAccount()
{}

////---------------------------------------------------------------------------
////user defined functions
////---------------------------------------------------------------------------
bool SavingsAccount::canTransferOut(double amountToTransfer) const {
	return ((maxBorrowable() - amountToTransfer) >= this->getMinimumBalance());
}
double SavingsAccount::getMinimumBalance() const {
	return minimumBalance_;
}
bool SavingsAccount::canWithdraw(double amountToWithdraw) const {
	//check if enough money in account
	return ((maxBorrowable() - amountToWithdraw) >= this->getMinimumBalance());
}
