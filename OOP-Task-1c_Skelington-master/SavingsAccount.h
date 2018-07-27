//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#ifndef SavingsAccountH
#define SavingsAccountH

//---------------------------------------------------------------------------
//SavingsAccount: class declaration
//---------------------------------------------------------------------------


#include "BankAccount.h"

//make in to abstract class

class SavingsAccount : public BankAccount {
public:
	//constructors & destructor
	SavingsAccount();
	~SavingsAccount();

	//functions
	virtual double getMinimumBalance() const;
	virtual bool canWithdraw(double amount) const;
	virtual bool canTransferOut(double amount) const;

private:
	//data items
	double minimumBalance_;
};
#endif