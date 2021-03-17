#include <iostream>



int main() {
   int number = 3428;
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
    		morv = 'M';
    		return morv;
    	} else if (digit3 > digit4) {
    		morv = 'V';
    		return morv;
    	}
    	else {
    		return morv;
    	}
    }
    else if ((digit1 == -1) && (digit2 != -1) && (digit3 != -1) && (digit4 != -1)) {
    	if ((digit2 < digit3) && (digit3 > digit4)) {
    		morv = 'M';
    		return morv;
    	}
    	else if ((digit2 > digit3) && (digit3 < digit4)) {
    		morv = 'V';
    		return morv;
    	}
    	else {
    		return morv;
    	}
    }
    else if (digit1 != -1) {
    	if ((digit1 < digit2) && (digit2 > digit3) && (digit3 < digit4)) {
    		morv = 'M';
    		return morv;
    	}
    	else if ((digit1 > digit2) && (digit2 < digit3) && (digit3 > digit4)) {
    		morv = 'V';
    		return morv;
    	}
    }
    std::cout << morv << std::endl;
}