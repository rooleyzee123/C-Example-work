//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#ifndef BankAccountH
#define BankAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"

#include <fstream>
#include <cassert>
using namespace std;


class BankAccount {
public:
    //constructors & destructor
	BankAccount();
    ~BankAccount();

	//abstract definition
	virtual void abstract() = 0;

	//getter (assessor) functions
    const string getAccountNumber() const;
    const Date getCreationDate() const;
	double getBalance() const;
    bool	isEmptyTransactionList() const;

	//other operations
	const string prepareFormattedStatement() const;

    virtual void recordDeposit(double amount);

	virtual double maxBorrowable() const;
	virtual bool canWithdraw(double amount) const;
	virtual bool canDeposit(double amount) const;
	virtual bool canTransferOut(double amount) const;
	virtual bool canTransferIn(double amount) const;
    void recordWithdrawal(double amount);
	void recordTransferOut(double transferAmount, string tAN);
	void recordTransferIn(double transferAmount, string aAN);

	void readInBankAccountFromFile(const string& fileName);
	void storeBankAccountInFile(const string& fileName) const;
	//functions to put data into and get data from streams
	ostream& putDataInStream(ostream& os) const;
	ostream& putAccountDetailsInStream(ostream& os) const;
	istream& getDataFromStream(istream& is);
	istream& getAccountDataFromStream(istream& is);

	const string prepareFormattedAccountDetails() const;
	const string prepareFormattedTransactionList() const;
	const string prepareFormattedTransactionList(TransactionList transactionList) const;

	static const string getAccountType(const string& filename);
	static const string getAccountType(char n);

	//user defined functions
	const TransactionList getDeposits() const;
    const TransactionList getTransactions() const;
	const TransactionList getTransactions(int amountToShow) const;
	const string prepareFormattedMiniDetails() const;
	TransactionList getTransactionsUpToDate(Date) const;
	void deleteTransactionsUpToDate(TransactionList deleteList, Date date);
	//double produceNMostRecentTransactions(int n, string& transactionList) const;
	
private:
    //data items
    string accountNumber_;
 
	//support functions
	ostream& putTransactionInStream(ostream& os) const;
	istream& getTransactionsDataFromStream(istream& is);

protected:
	//data items
    Date   creationDate_;
	double balance_;
    TransactionList transactions_;

	//support functions
	void updateBalance(double amount);

};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const BankAccount&);	//output operator
istream& operator>>(istream&, BankAccount&);	    //input operator

#endif
