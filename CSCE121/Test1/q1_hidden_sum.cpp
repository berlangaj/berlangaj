#include <iostream>
#include <string>

using std::cout, std::cin, std::endl;

int sum(int number) { //create int function that returns the sum of the even ints or 0 if number starts with 4
//im going to convert number to string and analyze that way
	string newNumber = "";
	int answer = 0;
	while (number > 0) { //turn each digit into string


	}

	if(newNumber.at(0) == '4') { //if first number starts with 4, return 0
		answer = 0;
		return answer;
	}
	for (unsigned int i = 0; i < newNumber.size()-1; i++) { //use loop to check if digit is even
		if(newNumber.at(i))
	}
}



int main () {
}