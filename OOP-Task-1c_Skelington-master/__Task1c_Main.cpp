//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 16
//Team: Dion Perez-France, Daniel Rose, Zak Bond, Zak Rooley

#include "ATM.h"         //include modules header files

//---------------------------------------------------------------------------

//main application

int main() { 
	//create the application
	ATM theATM; // default constructor called here
    //run it
	theATM.activateCashPoint();
	//destroy it - destructor called here
	return 0;
}
