//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#ifndef CurrentAccountH
#define CurrentAccountH

//---------------------------------------------------------------------------
//CurrentAccount: class declaration
//---------------------------------------------------------------------------


#include "BankAccount.h"


class CurrentAccount : public BankAccount {
public:
	//constructors & destructor
	CurrentAccount();
	~CurrentAccount();

	void abstract() {};

	double getOverdraftLimit() const;
	virtual double maxBorrowable() const;
	virtual bool canWithdraw(double amount) const;

	

private:
	//data items
	double overdraftLimit_;
};
#endif
