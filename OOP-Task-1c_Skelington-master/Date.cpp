//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#include "Date.h"

//---------------------------------------------------------------------------
//Date: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors
Date::Date() 						//default constructor
: day_(0), month_(0), year_(0)
{}
Date::Date(int d, int m, int y) 	//constructor
: day_(d), month_(m), year_(y)
{}

//____other public member functions
int Date::getDay() const {
	return day_;
}
int Date::getMonth() const {
	return month_;
}
int Date::getYear() const {
	return year_;
}
const Date Date::currentDate() {	//returns the current date
	time_t now(time(0));
	struct tm t;
	localtime_s(&t, &now);
	return Date(t.tm_mday, t.tm_mon + 1,  t.tm_year + 1900);
}
void Date::setDate(int d, int m, int y) {
	day_ = d;
	month_ = m;
	year_ = y;
}
string Date::toFormattedString() const {
//return date formatted as string ("DD/MM/YYYY")
	ostringstream os;
	os << setfill('0');
	os << setw(2) << day_ << "/";
	os << setw(2) << month_ << "/";
	os << setw(4) << year_;
	return (os.str());
}

ostream& Date::putDataInStream(ostream& os) const {
//put (unformatted) date (D/M/Y) into an output stream
	os << day_ << "/";
	os << month_ << "/";
	os << year_;
	return os;
}
istream& Date::getDataFromStream(istream& is) {
//read in date from (semi-formatted) input stream (D/M/Y)
	char ch;			//(any) colon field delimiter
	is >> day_ >> ch >> month_ >> ch >> year_;
	return is;
}

//---------------------------------------------------------------------------
//user defined
//---------------------------------------------------------------------------
bool Date::readInValidDate(const Date& creationDate, int day, int month, int year) {
	//if the month has more than 31 days etc
	bool legitDay;
	bool legitMonth;
	bool legitDate;
	string temp; //temporarily storing the user's entry so it's not in base 8 (08 etc.)
	temp = to_string(month);

	if (month <= 12)
		legitMonth = true;
	else legitMonth = false;

	//logic to set months to string for comparing them in the below switch statement
	if (temp == "01") month = 1; if (temp == "02") month = 2; if (temp == "03") month = 3; if (temp == "04") month = 4;
	if (temp == "05") month = 5; if (temp == "06") month = 6; if (temp == "07") month = 7; if (temp == "08") month = 8;
	if (temp == "09") month = 9; if (temp == "10") month = 10; if (temp == "11") month = 11; if (temp == "12") month = 12;

	switch (month) { 
	case 1: 
	{
		if (day > 31) { //not a valid date, 
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	case 2: {
		if (day > 28) {
			return false;
		}
		else {
			legitDay = true;
		break;
		}
	}
	case 3: {
		if (day > 31) { //not a valid date, 
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	case 4: 
	{
		if (day > 30) {
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	case 5: {
		if (day > 31) { //not a valid date, 
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	case 6: 
	{
		if (day > 30) {
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	case 7:
	{
		if (day > 31) { //not a valid date, 
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	case 8: {
		if (day > 31) { //not a valid date, 
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	case 9: 
	{
		if (day > 30) {
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	case 10: {
		if (day > 31) { //not a valid date, 
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	case 11: 
	{
		if (day > 30) {
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	case 12: {
		if (day > 31) { //not a valid date, 
			return false;
		}
		else {
			legitDay = true;
			break;
		}
	}
	default: legitDay = true, legitMonth = true;
	}
	
	//Make a new temp date to compare to the creationDate
	Date tempDate(day, month, year);
	//if creationDate is younger than user's date...
	if (creationDate < tempDate && tempDate < currentDate()) {
		legitDate = true;
	}
	else {
		legitDate = false;
	}

	if (legitMonth == true && legitDay == true && legitDate == true) {
	return true; //valid date
	}
	else {
		return false; //invalid date
	}
}

//---------------------------------------------------------------------------
//overloaded operator functions
//---------------------------------------------------------------------------

bool Date::operator==(const Date& d) const { //comparison operator
	return
		((day_ == d.day_) &&
		 (month_ == d.month_) &&
		 (year_ == d.year_));
}
bool Date::operator!=(const Date& d) const {
	return (!(*this == d));
}
bool Date::operator<(const Date& d) const { //NEW
//true if (strictly) earlier than d (i.e., *this < d)
	return ((year_ < d.year_)
	     || ((year_ == d.year_) && (month_ < d.month_) )
	     || ((year_ == d.year_) && (month_ == d.month_) && (day_ < d.day_)));
}

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Date& aDate) {
    return (aDate.putDataInStream(os));
}
istream& operator>>(istream& is, Date& aDate) {
	return (aDate.getDataFromStream(is));
}
