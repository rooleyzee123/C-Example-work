//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley


#pragma once
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------

#include "constants.h"
#include "Date.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class UserInterface {
public:
	void showByeScreen() const;

	int showMainMenuAndGetCommand() const;
	int showCardMenuAndGetCommand(const string& cardNum) const;
	int showAccountMenuAndGetCommand(const string& accNum) const;

	void showErrorInvalidCommand() const;
	void wait() const;
	void endProgram() const;
	const string readInCardToBeProcessed() const;
	void showValidateCardOnScreen(int validCode, const string& cardNum) const;
	void showCardAccounts(const string& cardNum, const string& cardSt) const;
	const string readInAccountToBeProcessed() const;
	const double readInTransferAmount() const;
	void showValidateAccountOnScreen(int valid, const string& acctNum) const;
	void showCurrentTimeAndDate(string currentDateTime) const;
	void showCardOnScreen(const string cardDetails) const;
	void showTransferOnScreen(bool trOutOK, bool trInOK, double transferAmount) const;

	static const string cardFilename(const string& cn);
	static const string accountFilename(const string& an);

	double readInWithdrawalAmount() const;
	double readInDepositAmount() const;

	void showProduceBalanceOnScreen(double bal) const;
	void showDepositOnScreen(bool auth, double deposit) const;
	void showWithdrawalOnScreen(bool auth, double withdrawal) const;
	void showStatementOnScreen(const string&) const;

	//User defined
	void showAllDepositsOnScreen(const bool noTransactions, const string& deposits) const;
	int readInTransactions() const;
	void showMiniStatement(const string&) const;
	void showNoTransactions() const;
	int showOptionMenu() const;
	double readInAmount() const;
	string readInTitle() const;
	Date readInDate(Date creationDate) const;
	const bool confirmDeletion() const;
	void deletionConfirmed() const;
	void deletionCancelled() const;
	void showMatchingTransactionsBySearch(double amount, int& n, string& search) const;
	void showMatchingTransactionsBySearch(string title, int& n, string& search) const;
	void showMatchingTransactionsBySearch(Date date, int& n, string& search) const;
	void showFundsAvailableOnScreen(bool empty, string mad, double Funds) const;
	void showTransactionsUpToDateOnScreen(bool isEmpty, Date date, int sizeOfList, string formattedString) const;

private:
	//support functions
	int readInCommand() const;
	double readInPositiveAmount() const;
	void outputHeader(const string&) const;
	string askForInput(const string&) const;
	void outputLine(const string&) const;

};


