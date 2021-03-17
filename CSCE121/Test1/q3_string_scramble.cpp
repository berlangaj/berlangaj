#include <iostream>
#include <string>

using std::cout, std::cin, std::endl, std::string;

string scrambleWord(string word);

int main() {
	return 0;
}

string scrambleWord(string word) {
	for (unsigned int i = 2; i < (word.size() - 2); i++) { //create loop to analyze string, start at i = 2 since first two cant be switched, and end 2 before so last word cant be switched
		if ((i % 2) != 0) {//if string index is odd then switch with one letter before
			std::swap(word.at(i), word.at(i-1));
		}  
	}
}
