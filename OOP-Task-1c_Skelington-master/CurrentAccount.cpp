//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#include "CurrentAccount.h"

//---------------------------------------------------------------------------
//CurrentAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

CurrentAccount::CurrentAccount()
: BankAccount(), overdraftLimit_(10000.0)
{}
CurrentAccount::~CurrentAccount()
{}

////---------------------------------------------------------------------------
////user defined functions
////---------------------------------------------------------------------------
bool CurrentAccount::canWithdraw(double amountToWithdraw) const {
	//check if enough money in account
	return amountToWithdraw <= maxBorrowable();
}
double CurrentAccount::maxBorrowable() const {
	//return borrowable amount
	return (balance_ + overdraftLimit_);
}
double CurrentAccount::getOverdraftLimit() const {
	return overdraftLimit_;
}
