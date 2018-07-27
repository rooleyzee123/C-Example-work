//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#include "BankAccount.h"
#include "Constants.h"

//---------------------------------------------------------------------------
//BankAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

BankAccount::BankAccount()
	: balance_(0.0)
{}
BankAccount::~BankAccount()
{}


//____other public member functions

const string BankAccount::getAccountNumber() const {
	return accountNumber_;
}
const Date BankAccount::getCreationDate() const {
	return creationDate_;
}
double BankAccount::getBalance() const {
	return balance_;
}
bool BankAccount::isEmptyTransactionList() const {
	return transactions_.size() == 0;
}
//static
const string BankAccount::getAccountType(const string& filename) {
	return getAccountType(filename[13]); //14th char from the filename ("data/account_101.txt")
}
//static
const string BankAccount::getAccountType(char n) {
	//return account type ("BANK" for '0', "CURRENT" for '1', etc. or "UNKNOWN") 
	//(simply) identify type/class of account from the account number
	//'0' for bank account, '1' for current account, '2' for saving account, etc.
	switch (n)
	{
	case BANKACCOUNT_TYPE:		return "BANK"; 
	case CURRENTACCOUNT_TYPE:	return "CURRENT";
	case CHILDACCOUNT_TYPE:		return "CHILD";
	case ISAACCOUNT_TYPE:		return "ISA";
	default:					return "UNKNOWN";
	}
}

void BankAccount::recordDeposit(double amountToDeposit) {
	//create a deposit transaction
	Transaction aTransaction("deposit_to_ATM", amountToDeposit);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(amountToDeposit);			//increase balance_
}

double BankAccount::maxBorrowable() const {
	//return borrowable amount
	return balance_;
}
bool BankAccount::canWithdraw(double amountToWithdraw) const {
	//check if enough money in account
	return amountToWithdraw <= maxBorrowable();
}
bool BankAccount::canDeposit(double amountToDeposit) const {
	return true;
}
bool BankAccount::canTransferOut(double amountToTransfer) const {
	return amountToTransfer <= maxBorrowable();
}
bool BankAccount::canTransferIn(double amountToTransfer) const {
	return true;
}

void BankAccount::recordWithdrawal(double amountToWithdraw) {
	//create a withdrawal transaction
	Transaction aTransaction("withdrawal_from_ATM", -amountToWithdraw);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(-amountToWithdraw);			//decrease balance_
}
void BankAccount::recordTransferOut(double transferAmount, string tAN) {
	//create a transfer transaction
	Transaction aTransaction(("transfer_out_to_acct_" + tAN), -transferAmount);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(-transferAmount);
}
void BankAccount::recordTransferIn(double transferAmount, string aAN) {
	//create a transfer transaction
	Transaction aTransaction(("transfer_int_from_acct_" + aAN), transferAmount);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(transferAmount);
}
const string BankAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	//list of transactions (or message if empty)
	os << prepareFormattedTransactionList();
	return os.str();
}
void BankAccount::readInBankAccountFromFile(const string& fileName) {
	ifstream fromFile;
	fromFile.open(fileName.c_str(), ios::in); 	//open file in read mode
	if (fromFile.fail())
		cout << "\n      AN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
		fromFile >> (*this);  	//read  all info from bank account file
	fromFile.close();			//close file: optional here
}

void BankAccount::storeBankAccountInFile(const string& fileName) const {
	ofstream toFile;
	toFile.open(fileName.c_str(), ios::out);	//open copy file in write mode
	if (toFile.fail())
		cout << "\n      AN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
		toFile << (*this);	//store all info to bank account file
	toFile.close();			//close file: optional here
}
ostream& BankAccount::putDataInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	putAccountDetailsInStream(os);			//put bank account core information in stream
	putTransactionInStream(os);				//put all transactions in stream, one per line
	return os;
}
ostream& BankAccount::putTransactionInStream(ostream& os) const {
	if (transactions_.size() != 0)
		os << transactions_;				//put all transactions in stream, one per line
	return os;
}
ostream& BankAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	os << accountNumber_ << "\n";			//put account number
	os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	return os;
}
istream& BankAccount::getDataFromStream(istream& is) {
	//get BankAccount details from stream
	getAccountDataFromStream(is);			//get bank account ore information from stream
	getTransactionsDataFromStream(is);		//get all transactions from stream (if any)
	return is;
}
istream& BankAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	is >> accountNumber_;					//get account number
	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance
	return is;
}
istream& BankAccount::getTransactionsDataFromStream(istream& is) {
	is >> transactions_;					//get all transactions from stream (if any)
	return is;
}

//---------------------------------------------------------------------------
//user defined functions
//---------------------------------------------------------------------------
const TransactionList BankAccount::getDeposits() const {
	TransactionList transactToReturn;
	TransactionList copyOfTransactions = transactions_;
	while (copyOfTransactions.size() != 0) {
		Transaction t = copyOfTransactions.newestTransaction();
		//if amount is positive
		if (t.getAmount() >= 0) {
			transactToReturn.addNewTransaction(t);
		}
		copyOfTransactions.deleteFirstTransaction();
	}
	return transactToReturn;
}
const TransactionList BankAccount::getTransactions() const {
	return transactions_;
}
const TransactionList BankAccount::getTransactions(int amountToShow) const {
		//inputting N as most recent transactions, returning the total and giving transactionList a value
		TransactionList transactToReturn;
		TransactionList copyOfTransactions = transactions_;
		//instance of TransactionList to store the main transactions_ (list) values after conditional
			//number greater than existing size?
		if (amountToShow >= transactions_.size()) {
			transactToReturn = transactions_;
			//set it to current list and return
		}
		else {
			for (int i = 0; i < amountToShow; i++) {
				transactToReturn.addNewTransaction(copyOfTransactions.newestTransaction());
				copyOfTransactions.deleteGivenTransaction(copyOfTransactions.newestTransaction());
			}
		}
		return transactToReturn;
}

//could have these two functions as one, similar to prepareFormattedStatement
//but sequence diagram wants us to use mad and total vars

const string BankAccount::prepareFormattedMiniDetails() const {
	//same as prepareFormattedStatement, but for mini statement - 
	//no need for transaction list since done with produceNMostRecentTransactions
	assert(getAccountType(accountNumber_[0]) != "UNKNOWN");
	ostringstream os;

	os << "\n      ACCOUNT TYPE:    " << getAccountType(accountNumber_[0]) << " ACCOUNT";
	os << "\n      ACCOUNT NUMBER:  " << accountNumber_;
	os << "\n      CREATION DATE:   " << creationDate_.toFormattedString();
	os << fixed << setprecision(2) << setfill(' ');
	os << "\n      BALANCE WITHOUT OVERDRAFT:         \234" << setw(10) << balance_;
	os << "\n      BALANCE WITH OVERDRAFT:         \234" << setw(10) << maxBorrowable();
	os << "\n      ----------------------------------------";
	return os.str();
}

TransactionList BankAccount::getTransactionsUpToDate(Date dateToCheck) const {
	TransactionList newList = transactions_;
	TransactionList retList;
	while (newList.size() != 0) {
		Transaction t = newList.newestTransaction();
		if (t.getDate() < dateToCheck || t.getDate() == dateToCheck) {
			retList.addNewTransaction(t);
		}
		newList.deleteFirstTransaction();
	}
	return retList;
}

void BankAccount::deleteTransactionsUpToDate(TransactionList deleteList, Date date){
	TransactionList newList = transactions_;
	while (deleteList.size() > 0)
	{
		Transaction t = deleteList.newestTransaction();
		newList.deleteGivenTransaction(t);
		deleteList.deleteFirstTransaction();
	}
	transactions_ = newList;
}
//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------
void BankAccount::updateBalance(double amount) {
	balance_ += amount;   //add/take amount to/from balance_
}
const string BankAccount::prepareFormattedAccountDetails() const
{
	assert(getAccountType(accountNumber_[0]) != "UNKNOWN");
	ostringstream os;

	os << "\n      ACCOUNT TYPE:    " << getAccountType(accountNumber_[0]) << " ACCOUNT";
	os << "\n      ACCOUNT NUMBER:  " << accountNumber_;
	os << "\n      CREATION DATE:   " << creationDate_.toFormattedString();
	os << fixed << setprecision(2) << setfill(' ');
	os << "\n      BALANCE:         \234" << setw(10) << balance_;
	os << "\n      ----------------------------------------";
	return os.str();
}

const string BankAccount::prepareFormattedTransactionList() const
{
	ostringstream os;

	if (!transactions_.size() == 0)
	{
		os << "\n      TRANSACTIONS:";
		os << transactions_.toFormattedString();
	}
	else
	{
		os << "\n      NO TRANSACTIONS IN BANK ACCOUNT!";
	}

	return os.str();
}

const string BankAccount::prepareFormattedTransactionList(TransactionList transactionList) const
{
	ostringstream os;

	if (!transactionList.size() == 0)
	{
		os << "\n      TRANSACTIONS:";
		os << transactionList.toFormattedString();
	}
	else
	{
		os << "\n      NO TRANSACTIONS IN BANK ACCOUNT!";
	}

	return os.str();
}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const BankAccount& aBankAccount) {
	//put (unformatted) BankAccount details in stream
	return aBankAccount.putDataInStream(os);
}
istream& operator>>(istream& is, BankAccount& aBankAccount) {
	//get BankAccount details from stream
	return aBankAccount.getDataFromStream(is);
}
