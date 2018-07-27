//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#include "UserInterface.h" 

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

int numberOfTransactions = 0;

void UserInterface::wait() const
{
	cout << "\n";
	outputLine("Press RETURN to go back to menu...");
	char ch;
	cin.get(ch);
	cin.get(ch);
}
void UserInterface::endProgram() const
{
	cout << "\n";
	outputLine("Press RETURN to end program...");
	char ch;
	cin.get(ch);
	cin.get(ch);
}
int UserInterface::showMainMenuAndGetCommand() const
{
	system("cls");
	cout << "\n\n";
	outputHeader("WELCOME TO THE ATM");
	outputLine(" 0                            Leave ATM ");
	outputLine(" 1                      Enter your card ");
	outputLine("----------------------------------------");
	return (readInCommand());
}

int UserInterface::showAccountMenuAndGetCommand(const string& accNum) const
{
	outputHeader("ACCOUNT " + accNum + " MENU");
	outputLine(" 0                    Back to card menu ");
	outputLine(" 1                      Display balance ");
	outputLine(" 2                Withdraw from account ");
	outputLine(" 3                 Deposit into account ");
	outputLine(" 4                       Show statement ");
	outputLine(" 5                    Show all deposits ");
	outputLine(" 6                  Show mini statement ");
	outputLine(" 7                  Search Transactions ");
	outputLine(" 8    Clear all transactions up to date ");
	outputLine(" 9          Transfer to another account ");
	outputLine("----------------------------------------");
	return (readInCommand());
}

const string UserInterface::readInCardToBeProcessed() const {
	return askForInput("ENTER YOUR CARD NUMBER");
}

void UserInterface::showValidateCardOnScreen(int validCode, const string& cardNumber) const
{
	switch (validCode)
	{
	case VALID_CARD: {
		// Card exists and is accessible (and is not already open: TO BE IMPLEMENTED)
	} break;
	case UNKNOWN_CARD: {
		outputLine("ERROR: CARD " + cardNumber + " DOES NOT EXIST");
	} break;
	case EMPTY_CARD: {
		outputLine("ERROR: CARD " + cardNumber + " DOES NOT LINK TO ANY ACCOUNTS");
	} break;
	}
}

int UserInterface::showCardMenuAndGetCommand(const string& cardNumber) const
{
	outputHeader("CARD " + cardNumber + " MENU");
	outputLine(" 0           Stop banking & remove card ");
	outputLine(" 1            Manage individual account ");
	outputLine(" 2           Show total funds available  ");
	outputLine("----------------------------------------");
	return (readInCommand());
}

void UserInterface::showCardAccounts(const string& cardNumber, const string& cardDetails) const
{
	outputHeader("CARD " + cardNumber + " ACCOUNTS");
	cout << cardDetails;
	outputLine("----------------------------------------\n");
}


void UserInterface::showCardOnScreen(const string cardDetails) const{
	outputHeader("Choose an account to transfer to: ");
	cout << cardDetails;
	outputLine("----------------------------------------\n");
}

void UserInterface::showTransferOnScreen(bool trOutOK, bool trInOK, double transferAmount) const {
	outputHeader(to_string(transferAmount) + " has been transfered");
}
const string UserInterface::readInAccountToBeProcessed() const {
	return askForInput("SELECT ACCOUNT TO MANAGE");
}

const double UserInterface::readInTransferAmount() const {
	double amount;
	outputLine("ENTER AMOUNT: ");
	cin >> amount;
	return amount;
}

void UserInterface::showValidateAccountOnScreen(int validCode, const string& accNum) const
{
	switch (validCode)
	{
	case VALID_ACCOUNT:
	{
		// Account exists and is accessible with that card (and not already open: TO BE IMPLEMENTED)
	} break;
	case INVALID_ACCOUNT_TYPE:
	{
		outputLine("ERROR: ACCOUNT " + accNum + " IS NOT A RECOGNISED TYPE OF ACCOUNT!");
	} break;
	case UNKNOWN_ACCOUNT:
	{
		outputLine("ERROR: ACCOUNT " + accNum + " DOES NOT EXIST!");
	} break;
	case UNACCESSIBLE_ACCOUNT:
	{
		outputLine("ERROR: ACCOUNT " + accNum + " IS NOT ACCESSIBLE WITH THIS CARD!");
	} break;
	}
}

void UserInterface::showCurrentTimeAndDate(string currentDateTime) const
{
	cout << currentDateTime;
}

//static 
const string UserInterface::cardFilename(const string& cn) {
	//read in card name & produce cashcard filename
	return FILEPATH + "card_" + cn + ".txt";	//read in card name & produce cashcard filename
}
//static
const string UserInterface::accountFilename(const string& an) {
	return FILEPATH + "account_" + an + ".txt";
}

//input functions

double UserInterface::readInWithdrawalAmount() const {
	//ask for the amount to withdraw
	outputLine("AMOUNT TO WITHDRAW: \234");
	return (readInPositiveAmount());
}
double UserInterface::readInDepositAmount() const {
	//ask for the amount to deposit
	outputLine("AMOUNT TO DEPOSIT: \234");
	return (readInPositiveAmount());
}


//output functions

void UserInterface::showProduceBalanceOnScreen(double balance) const
{
	cout << "\n      THE CURRENT BALANCE IS: " << fixed << setprecision(2) << setfill(' ') << "\234" << setw(12) << balance;
}

void UserInterface::showWithdrawalOnScreen(bool trAuthorised, double withdrawnAmount) const
{
	if (trAuthorised)
	{
		cout << "\n      TRANSACTION AUTHORISED. \234" << setw(0) << withdrawnAmount << " WITHDRAWN FROM ACCOUNT";
	}
	else
	{
		outputLine("TRANSACTION IMPOSSIBLE!"); // not enough money
	}
}

void UserInterface::showDepositOnScreen(bool trAuthorised, double depositAmount) const
{
	if (trAuthorised)
	{
		cout << "\n      TRANSACTION AUTHORISED. \234" << setw(0) << depositAmount << " DEPOSITED INTO ACCOUNT";
	}
	else
	{
		outputLine("TRANSACTION IMPOSSIBLE!"); // too much to deposit
	}
}
void UserInterface::showStatementOnScreen(const string& statement) const {
	outputHeader("PREPARING STATEMENT...");
	cout << statement;
	outputLine("----------------------------------------\n");
}

//---------------------------------------------------------------------------
// user defined functions
//---------------------------------------------------------------------------
void UserInterface::showAllDepositsOnScreen(const bool noTransactions, const string& deposits) const {
	outputHeader("PREPARING DEPOSITS");
	
	if (noTransactions) {
		cout << "NO TRANSACTIONS MADE";
	}
	else {
		cout << deposits;
	}
	outputLine("----------------------------------------\n");
}

int UserInterface::readInTransactions() const {
	// checks for total number of transactions, ready to show later
	outputLine("HOW MANY TRANSACTIONS WOULD YOU LIKE TO SEE?");
	return (readInPositiveAmount()); //calls readInPos to make sure that number isn't negative
}

void UserInterface::showMiniStatement(const string& statement) const {
	outputHeader("PREPARING STATEMENT...");
	cout << statement;
	outputLine("----------------------------------------\n");
}

void UserInterface::showNoTransactions() const {
	//for if there's no transactions made/available
	outputHeader("NO AVAILABLE TRANSACTIONS TO SHOW...");
}

int UserInterface::showOptionMenu() const {
	outputHeader("PLEASE SELECT AN OPTION:");
	outputLine(" 1                    Search by amount ");
	outputLine(" 2                    Search by title ");
	outputLine(" 3                    Search by date ");
	return(readInCommand());
}

double UserInterface::readInAmount() const {
	double amount;
	outputLine("ENTER AMOUNT: ");
	cin >> amount;
	return amount;
}

string UserInterface::readInTitle() const {
	string title;
	outputLine("ENTER A TITLE: ");
	cin >> title;

	while (title == "") {
		outputLine("INVALID TITLE, PLEASE TRY AGAIN: ");
		cin >> title;
	}
	return title;
}

Date UserInterface::readInDate(Date creationDate) const {
	Date date;
	int day, month, year;
	bool validDate;

	do {
		outputLine("ENTER A DAY: ");
		cin >> day;
		outputLine("ENTER A MONTH: ");
		cin >> month;
		outputLine("ENTER A YEAR: ");
		cin >> year;
		date.setDate(day, month, year);
		validDate = date.readInValidDate(creationDate, day, month, year);
		if (!validDate) {
		outputLine("INVALID DATE, PLEASE TRY AGAIN");
		}
	} while (validDate == false);

	return date;
}
const bool UserInterface::confirmDeletion() const {
	outputLine("ARE YOU SURE YOU WANT TO DELETE THESE TRANSACTIONS?");
	outputLine("THEY WILL BE GONE FOREVER (A LONG TIME).");
	outputLine("1 TO CONFIRM, 2 TO CANCEL");
	if (readInCommand() == 1) {
		return true;
	}
	else 
		return false;
}

void UserInterface::showMatchingTransactionsBySearch(double amount, int& numOfTransactions, string& search) const {
	//number of transactions greater than 0
	if (numOfTransactions > 0) {
		cout << "THERE ARE " << numberOfTransactions << " THAT MATCH THE SEARCH TERM\n";
	}
	else {
		cout << "THERE ARE 0 TRANSACTIONS THAT MATCH THE SEARCH TERM";
	}
}
void UserInterface::showMatchingTransactionsBySearch(string title, int& numOfTransactions, string& search) const {
	if (numOfTransactions > 0) {
		cout << "THERE ARE " << numberOfTransactions << " THAT MATCH THE SEARCH TERM\n";
	}
	else {
		cout << "THERE ARE 0 TRANSACTIONS THAT MATCH THE SEARCH TERM";
	}
}
void UserInterface::showMatchingTransactionsBySearch(Date date, int& numOfTransactions, string& search) const {
	if (numOfTransactions > 0) {
		cout << "THERE ARE " << numberOfTransactions << " THAT MATCH THE SEARCH TERM\n";
	}
	else {
		cout << "THERE ARE 0 TRANSACTIONS THAT MATCH THE SEARCH TERM";
	}
}
void UserInterface::showFundsAvailableOnScreen(bool empty, string mad, double Funds) const
{
	if (empty == false)
	{

		cout << mad;
		cout << "\n      Total amount across accounts " << Funds;
	}
	else
	{
		cout << "\n      NO ACCOUNT ACCESSIBLE WITH THIS CARD!";
	}
}
void UserInterface::showTransactionsUpToDateOnScreen(bool isEmpty, Date date, int sizeOfList, string formattedString) const {
	if (isEmpty) {
		outputLine("NO TRANSACTIONS");
	}
	else {
		showMiniStatement(formattedString);
	}
}
void UserInterface::deletionConfirmed() const {
	outputLine("TRANSACTIONS DELETED");
}
void UserInterface::deletionCancelled() const {
	outputLine("DELETION CANCELLED");
}
//---------------------------------------------------------------------------
// private support member functions
//---------------------------------------------------------------------------

void UserInterface::showByeScreen() const
{
	outputLine("");
	outputHeader("THANK YOU FOR USING THE ATM");
	endProgram();
}

int UserInterface::readInCommand() const
{
	cout << "\n";
	outputLine("ENTER YOUR COMMAND: ");
	int com;
	cin >> com;
	return com;
}

void UserInterface::showErrorInvalidCommand() const
{
	outputLine("INVALID COMMAND CHOICE, TRY AGAIN");
}

double UserInterface::readInPositiveAmount() const
{
	double amount;
	cin >> amount;

	while (amount <= 0.0)
	{
		outputLine("AMOUNT SHOULD BE A POSITIVE AMOUNT, TRY AGAIN: ");
		cin >> amount;
	}

	return amount;
}

void UserInterface::outputHeader(const string& header) const
{
	// calculate lengths so we can centre the header
	const int length = header.size();
	const int borderWidth = 40;
	const int leftSpacePad = 6;
	const int paddingRequired = ((borderWidth - length) / 2) + leftSpacePad;

	outputLine("========================================");
	cout << "\n" << setfill(' ') << setw(paddingRequired) << ' ' << header;
	outputLine("========================================");
}

string UserInterface::askForInput(const string& promptForUser) const
{
	outputLine(promptForUser + ": ");
	string userInput;
	cin >> userInput;
	return userInput;
}

void UserInterface::outputLine(const string& text) const
{
	cout << "\n      " << text;
}