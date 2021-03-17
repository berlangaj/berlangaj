#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	if ((a >= 10) && (a <= b) && (b < 10000)) {
		return true;
	} else {
		return false;
	}
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	int digit4 = -1;
   	int digit3 = -1;
   	int digit2 = -1;
   	int digit1 = -1;

   	//evaluates each digit
   	while(number != 0) {
    	digit4 = number % 10;
    	number /= 10;
		if (number == 0)
      		break;
      	digit3 = number %10;
      	number /= 10;   
      	if (number == 0)
      		break;
      	digit2 = number % 10;
      	number /= 10;
      	if (number == 0)
      		break; 
      	digit1 = number % 10;
      	number /= 10;
    }
    
    if ((digit1 == -1) && (digit2 == -1) && (digit3 != -1) && (digit4 != -1)) {
    	if (digit3 < digit4) {
    		return 'M';
    	} else if (digit3 > digit4) {
    		return 'V';
    	} else {
    		return 'N';
    	}
    }
    else if ((digit1 == -1) && (digit2 != -1) && (digit3 != -1) && (digit4 != -1)) {
    	if ((digit2 < digit3) && (digit3 > digit4)) {
    		return 'M';
    	}
    	else if ((digit2 > digit3) && (digit3 < digit4)) {
    		return 'V';
    	} else {
    		return 'N';
    	}
    } else {
    	if ((digit1 < digit2) && (digit2 > digit3) && (digit3 < digit4)) {
    	
    		return 'M';
    	}
    	else if ((digit1 > digit2) && (digit2 < digit3) && (digit3 > digit4)) {
    		return 'V';
    	} else {
    		return 'N';
    	}
    } 

}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	//use for statement 
	int numMountains = 0;
	int numValleys = 0;
	int numNeither = 0;
	for (int i = a; i <= b; i++) {
		if (classify_mv_range_type(i) == 'M') {
			numMountains += 1;
		}
		else if (classify_mv_range_type(i) == 'V') {
			numValleys += 1;
		}
		else {
			numNeither += 1;
		}
		
	}
	std::cout << "There are " << numMountains << " mountain ranges and " << numValleys << " valley ranges between " << a << " and " << b << "." << std::endl;




}