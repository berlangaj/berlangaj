#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	// TODO(student): print prompt for input
	int a;
	int b;
	cout << "Enter numbers 10 <= a <= b < 10000: " ;
	// TODO(student): read the numbers from standard input
	cin >> a >> b;

	// TODO(student): validate input (and reprompt on invalid input)
	while (!is_valid_range(a,b)) {
		cout << "Invalid Input" << endl;
		cout << "Enter numbers 10 <= a <= b < 10000: ";
		cin >> a >> b;
	} if (is_valid_range(a,b)) {// TODO(student): compute and display solution
		count_valid_mv_numbers(a,b);
	}	
	
	return 0;
}