//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#ifndef ATMH
#define ATMH 

//---------------------------------------------------------------------------
//ATM: class declaration
//---------------------------------------------------------------------------

#include "Card.h"
#include "BankAccount.h"
#include "CurrentAccount.h"
#include "ChildAccount.h"
#include "ISAAccount.h"
#include "UserInterface.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

class ATM {
public:
	ATM();	//default constructor
	~ATM();	//destructor
    void activateCashPoint();
private:
	//data items
    BankAccount* p_theActiveAccount_;
    Card* p_theCard_;
    const UserInterface theUI_;

	//support functions
    int  validateCard(const string&) const;
	void executeCardCommand(int);
	int  validateAccount(const string&) const;
	void executeAccountCommand();
 
	//card menu commands
	void m_card1_manageIndividualAccount();
	void m_card2_showFundsAvailableOnAllAccounts();
	//account menu commands
    void m_acct1_produceBalance() const;
    void m_acct2_withdrawFromBankAccount();
    void m_acct3_depositToBankAccount();
    void m_acct4_produceStatement() const;
	void m_acct5_showAllDeposits() const;
	void m_acct6_showMiniStatement() const;
	void m_acct7_searchForTransactions() const;
	void m_acct8_clearTransactionsToDate() const;
	void m_acct9_transferCashToAnotherAccount();

	//user defined
	void searchAllTransactions() const;
	void showTransactionsByAmount() const;
	void showTransactionsByTitle() const;
	void showTransactionsByDate() const;
	Date getCreationDate() const;
	void produceTransactionsUpToDate(bool empty, Date date) const;
	void deleteTransactionsUpToDate();

    //support file handling functions and creation of dynamic objects
    bool canOpenFile(const string&) const;
	static char getAccountTypeCode(const string&);
	bool accountsListedOnCard(const string&) const;

    void activateCard(const string&);
	void releaseCard();
	
	void attemptTransfer(BankAccount* otherAccount);
	void recordTransfer(double transferAmount, BankAccount* otherAccount);
	BankAccount* activateAccount(const string&);
	BankAccount* releaseAccount(BankAccount*, string);
};

#endif
