#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  // returns the length of the string including zero (0)
  return strlen(str);
}

unsigned int find(char str[], char character) {
  // returns 
  //  - the index of the first occurence of character in str
  //  - the size if the character is not found
	unsigned int index = 0;
  	for(unsigned int i = 0; i < strlen(str);i++) {
  		if (str[i] == character) {
  			return i;
  		}
  		index += 1;
  	}
  	return index;
}

bool equalStr(char str1[], char str2[]) {
  // returns true if they are equal and false if they are not
	int result;
	result = strcmp(str1, str2);
	if (result == 0) {
		return true;
	}
	else {
		return false;
	}
}