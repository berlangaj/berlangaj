#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin, std::getline;
using std::string;

int main() {
	std::istringstream inSS;
	string userInput;
	string lhs;
	string ope; //operator
	string rhs;
	bool inputDone = false;

    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    while(!inputDone) { 
    	cout << ">> ";
    	getline(cin, userInput); //entire line into userInput
    	inSS.clear(); //clear stringstream
    	inSS.str(userInput); //copies into string buffer

    	inSS >> lhs; //checks first number to see if q or quit

    	if((lhs == "q") || (lhs == "quit")) {
    		inputDone = true;
    	}

    	else {  //if not q or quit, process operator and rhs
    		inSS >> ope;
    		inSS >> rhs;

    		if (ope == "+") {
    			cout << endl;
    			cout << "ans =" << endl;
    			cout << "    " << add(lhs,rhs) << endl;
    		}
    		else {
    			cout << endl;
    			cout << "ans =" << endl;
    			cout << "    " << multiply(lhs,rhs) << endl;
    		}

    	}
    }
    cout << endl;
    cout << "farvel!" << endl;

}

