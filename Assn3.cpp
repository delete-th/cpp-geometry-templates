#include <iostream> 
#include <fstream>
#include <string>
#include <limits>
#include "Functions.h"

using namespace std;

// Name: Thea Gardiola Saguid
// UOW No: 8691836
// Assignment 3
// Compile statement : g++ -std=c++11 

int main()
{
	int userInput = 0;
	
	while (userInput != 7) 
	{
		displayMenu();
		cin >> userInput;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore newline from enter choice 
		
		// handle non-integer input
		if (cin.fail()) {
			cin.clear(); 	// clear error state
			// discard invalid input
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			cout << "\nNot an option. Select again.\n";
			continue;
		}
		
		cout << endl;
		
		// handle integer out of range
		if (userInput < 1 || userInput > 7) {
			cout << "Not an option. Select again.\n";
			continue;
		}
		
		// valid input
		switch (userInput) 
		{
			case 1: option1(); 
					break;
			case 2: option2(); 
					break;
			case 3: option3();
					break;
			case 4: option4();
					break;
			case 5: option5();
					promptUser();
					break;
			case 6: option6();
					break;
			case 7: exitProgram();
					break;
			
		}
	}
	
	return 0;
}

