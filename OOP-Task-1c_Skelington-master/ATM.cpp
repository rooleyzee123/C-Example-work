//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#include "ATM.h"

//---------------------------------------------------------------------------
//ATM: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

ATM::ATM()
	: p_theActiveAccount_(nullptr), p_theCard_(nullptr), theUI_()
{}

ATM::~ATM()
{
	assert(p_theActiveAccount_ == nullptr);
	assert(p_theCard_ == nullptr);
}

//____other public member functions

void ATM::activateCashPoint() {
	int command( theUI_.showMainMenuAndGetCommand());
	while (command != QUIT_COMMAND)
	{
		executeCardCommand(command);
		theUI_.wait();
		command = theUI_.showMainMenuAndGetCommand();
	}
	theUI_.showByeScreen();
}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void ATM::executeCardCommand(int option) {
	switch (option)
	{
		case 1:
		{
			string cardNum(theUI_.readInCardToBeProcessed());
			string cardFilename(theUI_.cardFilename(cardNum));
			int validCardCode(validateCard(cardFilename));	
			theUI_.showValidateCardOnScreen(validCardCode, cardNum);
			if (validCardCode == VALID_CARD) 
			{
				//dynamically create a card and store card data
				activateCard(cardFilename);

				//select request for active card 
				int option = theUI_.showCardMenuAndGetCommand(cardNum);
				while (option != QUIT_COMMAND)
				{
					switch (option)
					{
					case 1: m_card1_manageIndividualAccount();
						break;
					case 2:m_card2_showFundsAvailableOnAllAccounts();
						break;
						default:
							theUI_.showErrorInvalidCommand();
					}

					theUI_.wait();
					option = theUI_.showCardMenuAndGetCommand(cardNum);
				}

				//free memory space used by active card
				releaseCard();
			}
			break;
		}
		default:theUI_.showErrorInvalidCommand();
	}
}
void ATM::m_card1_manageIndividualAccount() {
	assert(p_theCard_ != nullptr);
	theUI_.showCardAccounts(p_theCard_->getCardNumber(), p_theCard_->toFormattedString());
	executeAccountCommand();
}

//Task 3E
void ATM::m_card2_showFundsAvailableOnAllAccounts() {
	assert(p_theActiveAccount_ == nullptr);

	//get accounts list      activateCard(cardFilename)
	// bool for empty		 isEmpty
	//LOOP
	//while not empty		while(isEmpty != True)
	//loop each card		activateAccount(cardFilename?)
	//check max borrowable   maxBorrowable():			//add this to final number
	//text output			 prepareFormattedMiniDetails():				// This is the output for each card
	// close account		  releaseAccount*, string): BankAccount*
	//remove off list
	//loop back until list is empty

	//output total of all accounts together 

	List<string> accountList = p_theCard_->getAccountsList();
	string mad;
	double totalFund = 0;
	bool empty;
	if (accountList.isEmpty())
	{
		empty = true;
	}
	else
	{
	
		while (accountList.isEmpty() == false)
		{
			string temp;
			empty = false;

			p_theActiveAccount_ = activateAccount(theUI_.accountFilename(accountList.first()));			//makes account instance based off list
			totalFund += p_theActiveAccount_->maxBorrowable();											//gets maxfunds and adds to total var
			temp = p_theActiveAccount_->prepareFormattedMiniDetails() + "\n";							//prints out funds statement for that account
			releaseAccount(p_theActiveAccount_, accountList.first());									//drops instance of account
			accountList.deleteFirst();																	//removes the account opened within the loop from the list of accounts		
			mad = mad + temp;																			//Update mad string to have extended accounts											

		}
	}
	theUI_.showFundsAvailableOnScreen(empty,mad,totalFund);

}
int ATM::validateCard(const string& filename) const {
	//check that the card exists (valid)
	if (!canOpenFile(filename))   //invalid card
		return UNKNOWN_CARD;
	else
		//card empty (exist but no bank account listed on card)
		if (!accountsListedOnCard(filename))
			return EMPTY_CARD;
		else
			//card valid (exists and linked to at least one bank account)
			return VALID_CARD;
}
int ATM::validateAccount(const string& filename) const {
	//check that the account is valid 
	if (!canOpenFile(filename))
		//account does not exist
		return UNKNOWN_ACCOUNT;
	else
		//account type not recognised
		if (BankAccount::getAccountType(filename) == "UNKNOWN")
		//if (getAccountTypeCode(filename) == UNKNOWN_ACCOUNT_TYPE)
			return INVALID_ACCOUNT_TYPE;
		else
			//unaccessible account (exists but not listed on card)
			if (!p_theCard_->onCard(filename))
				return UNACCESSIBLE_ACCOUNT;
			else
				//account valid (exists and accessible)
				return VALID_ACCOUNT;
}
void ATM::executeAccountCommand() {
	assert(p_theActiveAccount_ == nullptr);
	//process from one account
	//select active account and check that it is valid
	const string anAccountNumber(theUI_.readInAccountToBeProcessed());
	const string bankAccountFilename(theUI_.accountFilename(anAccountNumber));
	const int validAccountCode(validateAccount(bankAccountFilename));
	theUI_.showValidateAccountOnScreen(validAccountCode, anAccountNumber);
	if (validAccountCode == VALID_ACCOUNT) //valid account: exists, accessible with card and not already open
	{
		//dynamically create a bank account to store data from file
		p_theActiveAccount_ = activateAccount(bankAccountFilename);

		//select request for active account 
		int option = theUI_.showAccountMenuAndGetCommand(p_theActiveAccount_->getAccountNumber());
		while (option != QUIT_COMMAND)
		{
			switch (option)
			{
				case 1:	m_acct1_produceBalance();
					break;
				case 2: m_acct2_withdrawFromBankAccount();
					break;
				case 3:	m_acct3_depositToBankAccount();
					break;
				case 4:	m_acct4_produceStatement();
					break;
				case 5: m_acct5_showAllDeposits();
					break;
				case 6: m_acct6_showMiniStatement();
					break;
				case 7: m_acct7_searchForTransactions();
					break;
				case 8: m_acct8_clearTransactionsToDate();
					break;
				case 9: m_acct9_transferCashToAnotherAccount();
					break;
				default:theUI_.showErrorInvalidCommand();
			}
			theUI_.wait();
			option = theUI_.showAccountMenuAndGetCommand(p_theActiveAccount_->getAccountNumber());   //select another option
		}	

		//store new state of bank account in file and free bank account memory space
		p_theActiveAccount_ = releaseAccount(p_theActiveAccount_, bankAccountFilename);
	}
}

//------ menu options
//---option 1
void ATM::m_acct1_produceBalance() const {
	assert(p_theActiveAccount_ != nullptr);
	double balance(p_theActiveAccount_->getBalance());
	theUI_.showProduceBalanceOnScreen(balance);
}
//---option 2
void ATM::m_acct2_withdrawFromBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToWithdraw(theUI_.readInWithdrawalAmount());
	bool transactionAuthorised(p_theActiveAccount_->canWithdraw(amountToWithdraw));
	if (transactionAuthorised)
	{   //transaction is accepted: money can be withdrawn from account
		p_theActiveAccount_->recordWithdrawal(amountToWithdraw);
	}   //else do nothing
	theUI_.showWithdrawalOnScreen(transactionAuthorised, amountToWithdraw);
}
//---option 3
void ATM::m_acct3_depositToBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToDeposit(theUI_.readInDepositAmount());
	p_theActiveAccount_->recordDeposit(amountToDeposit);
	theUI_.showDepositOnScreen(p_theActiveAccount_->canDeposit(amountToDeposit), amountToDeposit);
}
//---option 4
void ATM::m_acct4_produceStatement() const {
	assert(p_theActiveAccount_ != nullptr);
	theUI_.showStatementOnScreen(p_theActiveAccount_->prepareFormattedStatement());
}
//---option 5
void ATM::m_acct5_showAllDeposits() const {
	assert(p_theActiveAccount_ != nullptr);
	bool empty = p_theActiveAccount_->getTransactions().size() < 1; //no transactions
	theUI_.showAllDepositsOnScreen(empty, p_theActiveAccount_->getDeposits().toFormattedString());
}
//---option 6
void ATM::m_acct6_showMiniStatement() const {
	assert(p_theActiveAccount_ != nullptr);
	TransactionList transactions = p_theActiveAccount_->getTransactions(theUI_.readInTransactions());
	theUI_.showMiniStatement(p_theActiveAccount_->prepareFormattedTransactionList(transactions));
}
//---option 7
void ATM::m_acct7_searchForTransactions() const {
	assert(p_theActiveAccount_ != nullptr);
	bool empty = p_theActiveAccount_->isEmptyTransactionList();

	if (empty) {
		theUI_.showNoTransactions();
		return;
	}
	else {
		searchAllTransactions();
	}
}
//---option 8
void ATM::m_acct8_clearTransactionsToDate() const {
	assert(p_theActiveAccount_ != nullptr);
	bool empty = p_theActiveAccount_->isEmptyTransactionList();
	
	if (empty) {
		theUI_.showNoTransactions();
		return;
	}
	else {
		getCreationDate();
		produceTransactionsUpToDate(empty, theUI_.readInDate(getCreationDate()));
	}
}
//---option 9
void ATM::m_acct9_transferCashToAnotherAccount() {
	theUI_.showCardOnScreen(p_theCard_->toFormattedString());
	string targetAccountNum = theUI_.readInAccountToBeProcessed();
	const string targetAccountName = theUI_.accountFilename(targetAccountNum);
	const int validAccountCode(validateAccount(targetAccountName));
	theUI_.showValidateAccountOnScreen(validAccountCode, targetAccountName);
	if (validAccountCode == VALID_ACCOUNT)
	{ 
		BankAccount* p_transferTo = activateAccount(targetAccountName);
		attemptTransfer(p_transferTo);
		p_transferTo = releaseAccount(p_transferTo, targetAccountName);
	}
}
//------user defined (supporting functions)
void ATM::searchAllTransactions() const {
	int option; //which option the user chooses
	option = theUI_.showOptionMenu(); //showOptionMenu returns a number between 1-3
	
	switch (option) {
	case 1: showTransactionsByAmount();
		break;
	case 2: showTransactionsByTitle();
		break;
	case 3: showTransactionsByDate();
		break;
	default: theUI_.showErrorInvalidCommand();
	}
}
void ATM::showTransactionsByAmount() const {
	double amount;
	int numOfTransactions = 0;
	string search;

	//Read in the amount the user wants to search by
	amount = theUI_.readInAmount(); //need to define ui readInAmount and produceTransactions by in bankAccount

	//create two lists, new list is equal to all active transactions
	//ret list is empty and has individual transactions stored in them if the amount var - 
	// - is equal to the individual transaction 't'.
	//'t' is equal to the newest transaction from 'newList'
	TransactionList newList = p_theActiveAccount_->getTransactions();
	TransactionList retList;
	while (newList.size() != 0) {
		Transaction t = newList.newestTransaction();
		if (t.getAmount() == amount) {
			retList.addNewTransaction(t);
		}
		newList.deleteFirstTransaction();
	}
	//show a list of all transactions with the conditionally populated retList as the paramater
	theUI_.showMiniStatement(p_theActiveAccount_->prepareFormattedTransactionList(retList));
}
void ATM::showTransactionsByTitle() const {
	string title;
	int numOfTransactions = 0;
	string search;

	//Read in the title the user wants to search by: "Deposit" or "Withdrawal"
	title = theUI_.readInTitle();

	//create two lists, new list is equal to all active transactions
	//ret list is empty and has individual transactions stored in them if the string var, 'title' - 
	// - is equal to the individual transaction 't'.
	//'t' is equal to the newest transaction from 'newList'
	TransactionList newList = p_theActiveAccount_->getTransactions();
	TransactionList retList;
	while (newList.size() != 0) {
		Transaction t = newList.newestTransaction();

		//conditional logic checks for logical user entry
		if ((title == "Deposit") || (title == "deposit")) {
			title = "deposit_to_ATM";
		}
		else if ((title == "Withdrawal") || (title == "withdrawal")) {
			title = "withdrawal_from_ATM";
		}
		
		if (t.getTitle() == title) {
			retList.addNewTransaction(t);
		}
		newList.deleteFirstTransaction();
	}
	//show a list of all transactions with the conditionally populated retList as the paramater
	theUI_.showMiniStatement(p_theActiveAccount_->prepareFormattedTransactionList(retList));
}
void ATM::showTransactionsByDate() const {
	Date date;
	int numOfTransactions = 0;
	string search;

	//Read in the date to search by, in date format
	date = theUI_.readInDate(getCreationDate());

	//create two lists, new list is equal to all active transactions
	//ret list is empty and has individual transactions stored in them if the date var - 
	// - is equal to the individual transaction 't'.
	//'t' is equal to the newest transaction from 'newList'
	TransactionList newList = p_theActiveAccount_->getTransactions();
	TransactionList retList;
	while (newList.size() != 0) {
		Transaction t = newList.newestTransaction();
		if (t.getDate() == date) {
			retList.addNewTransaction(t);
		}
		newList.deleteFirstTransaction();
	}
	//show a list of all transactions with the conditionally populated retList as the paramater
	theUI_.showMiniStatement(p_theActiveAccount_->prepareFormattedTransactionList(retList));
}
Date ATM::getCreationDate() const {
	Date creationDate;
	creationDate = p_theActiveAccount_->getCreationDate();
	return creationDate;
}
void ATM::produceTransactionsUpToDate(bool empty, Date date) const {
	TransactionList dateList = p_theActiveAccount_->getTransactionsUpToDate(date);
	int size = dateList.size();
	string formattedList = p_theActiveAccount_->prepareFormattedTransactionList(dateList);

	theUI_.showTransactionsUpToDateOnScreen(empty, date, size, formattedList);
	bool deleteTransactions = theUI_.confirmDeletion();

	if (deleteTransactions == true) {
		p_theActiveAccount_->deleteTransactionsUpToDate(dateList, date);
		theUI_.deletionConfirmed();
		theUI_.showStatementOnScreen(p_theActiveAccount_->prepareFormattedStatement());
	}
	else {
		dateList = dateList;
		theUI_.deletionCancelled();
	}
}

//------private file functions

bool ATM::canOpenFile(const string& filename) const {
	//check if a file already exist
	ifstream inFile;
	inFile.open(filename.c_str(), ios::in); 	//open file
	//if does not exist fail() return true
	return (!inFile.fail());	//close file automatically when inFile goes out of scope
}

bool ATM::accountsListedOnCard(const string& cashCardFileName) const {
	//check that card is linked with account data
	ifstream inFile;
	inFile.open(cashCardFileName.c_str(), ios::in); 	//open file
	assert(!inFile.fail()); //file should exist at this point 
	//check that it contains some info in addition to card number
	string temp;
	inFile >> temp; //read card number
	inFile >> temp;	//ready first account data or eof if end of file found
	return (!inFile.eof());
}

void ATM::activateCard(const string& filename) {
	//dynamically create a cash card to store data from file
	//effectively create the cash card instance with the data
	assert(p_theCard_ == nullptr);
	p_theCard_ = new Card;
	assert(p_theCard_ != nullptr);
	p_theCard_->readInCardFromFile(filename);
}

void ATM::releaseCard() {
	//release the memory allocated to the dynamic instance of a card
	delete p_theCard_;
	p_theCard_ = nullptr;
}

void ATM::attemptTransfer(BankAccount* p_accountToTransferTo){
	double transferAmount = theUI_.readInTransferAmount();
	bool trOutOK = p_theActiveAccount_->canTransferOut(transferAmount);
	bool trInOK = p_accountToTransferTo->canTransferIn(transferAmount);
	if (trOutOK && trInOK)
	{
		recordTransfer(transferAmount, p_accountToTransferTo);
		theUI_.showTransferOnScreen(trOutOK, trInOK, transferAmount);
	}
}
void ATM::recordTransfer(double transferAmount, BankAccount* otherAccount) {
	string tAN = otherAccount->getAccountNumber();
	p_theActiveAccount_->recordTransferOut(transferAmount, tAN);
	string aAN = p_theActiveAccount_->getAccountNumber();
	otherAccount->recordTransferIn(transferAmount, aAN);
}


//static member function
char ATM::getAccountTypeCode(const string& filename) {
	//(simply) identify type/class of account from the account number
	//starts with 0 for bank account, 1 for current account, 2 for saving account, etc.
	return filename[13]; //14th char from the filename ("data/account_101.txt")
}

BankAccount* ATM::activateAccount(const string& filename) {
	//Pre-condition: type of the account is valid
	assert(BankAccount::getAccountType(filename) != "UNKNOWN");
	//effectively create the active bank account instance of the appropriate class
	//and store the appropriate data read from the file
	BankAccount* p_BA(nullptr);
	switch (getAccountTypeCode(filename))
	{
		case CURRENTACCOUNT_TYPE:
			p_BA = new CurrentAccount;
			break;
		case CHILDACCOUNT_TYPE:
			p_BA = new ChildAccount;
			break;
		case ISAACCOUNT_TYPE:
			p_BA = new ISAAccount;
			break;
			//default to CurrentAccount
		default: p_BA = new CurrentAccount;
	}
	assert(p_BA != nullptr); //check that the dynamic allocation has succeeded
	p_BA->readInBankAccountFromFile(filename); //read account details from file
	//use dynamic memory allocation: the bank account created will have to be released in releaseAccount
	return p_BA;
}

BankAccount* ATM::releaseAccount(BankAccount* p_BA, string filename) {
	//store (possibly updated) data back in file
	assert(p_BA != nullptr);
	p_BA->storeBankAccountInFile(filename);
	//effectively destroy the bank account instance
	delete p_BA;
	return nullptr;
}