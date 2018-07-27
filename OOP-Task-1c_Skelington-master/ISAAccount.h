//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#ifndef ISAAccountH
#define ISAAccountH

//---------------------------------------------------------------------------
//ISAAccount: class declaration
//---------------------------------------------------------------------------


#include "SavingsAccount.h"


class ISAAccount : public SavingsAccount {
public:
	//constructors & destructor
	ISAAccount();
	~ISAAccount();

	void abstract() {};

	double getMaximumYearlyDeposit() const;
	double getCurrentYearlyDeposit() const;
	Date getEndDepositPeriod() const;
	void recordDeposit(double amount);
	bool canTransferIn(double amount) const;
	bool canDeposit(double amount) const;



private:
	//data items
	double maximumYearlyDeposit_;
	double currentYearlyDeposit_;
	Date endDepositPeriod_;

	//functions
	void updateCurrentYearlyDeposit(double a);
};
#endif