//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#ifndef ChildAccountH
#define ChildAccountH

//---------------------------------------------------------------------------
//ChildAccount: class declaration
//---------------------------------------------------------------------------


#include "SavingsAccount.h"


class ChildAccount : public SavingsAccount {
public:
	//constructors & destructor
	ChildAccount();
	~ChildAccount();

	void abstract() {};

	double getMaximumPaidIn() const;
	double getMinimumPaidIn() const;
	void recordDeposit(double amount);
	bool canWithdraw(double amount) const;
	bool canTransferIn(double amount) const;
	bool canTransferOut(double amount) const;
	bool canDeposit(double amount) const;

private:
	//data items
	double minimumPaidIn_;
	double maximumPaidIn_;
};
#endif