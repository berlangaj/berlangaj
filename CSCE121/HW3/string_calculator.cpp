#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    if ((digit == '/') || (digit == '(') || (digit == '[') || (digit == '`') || (digit == '{') || (digit == '+') || (digit == '-') || (digit == '*') || (digit == '^') || (digit == ')') || (digit == ']') || (digit == '}')) {
        throw std::invalid_argument("invalid argument");
    }
    //convert char to str and then to unsigend int
    unsigned int decimal = digit - '0';
    return decimal;
}

char decimal_to_digit(unsigned int decimal) {
    if(decimal > 9) {
        throw std::invalid_argument("invalid argument");
    }
    char digit = decimal + '0';
    return digit;
}

string trim_leading_zeros(string num) {
    bool isNegative = false;
    if (num[0] == '-') {
        num.erase (0, 1);
        isNegative = true;
    }
    num.erase(0, std::min(num.find_first_not_of('0'), num.size()-1));
    if (num[0] == '0') {
        return num;
    }
    if (isNegative == true) {
        num.insert(0, 1, '-');
    }

    return num;
}

string add(string lhs, string rhs) {
    if(lhs.size() > rhs.size()) {    //make sure length of str rhs is bigger than lhs
        std::swap(lhs, rhs);
    }
    bool isNegative = false;
    if ((lhs[0] == '-') && (rhs[0] == '-')) { //take out negative signs
        lhs.erase(lhs.begin());
        rhs.erase(rhs.begin());
        isNegative = true;
    }
    string str = "";  //create an empty string
    int n1 = lhs.length(), n2 = rhs.length();  //calculate difference of length
    int diff = n2 - n1;
    
    


    int carry = 0;  //initial carry is 0
    for( int i = n1-1; i >= 0; i--) {   //start from the end of the string
        int sum = ((lhs[i] - '0') + (rhs[i+diff] - '0') + carry); //add digits and carry
        str.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    for (int i = n2-n1-1; i >= 0; i--) {  //add remaining digits
        int sum = ((rhs[i] - '0') + carry);
        str.push_back((sum % 10) + '0');
        carry = sum / 10;
    }
    if (carry) {
        str.push_back(carry + '0'); //add the extra carry
    }
    int n = (str.size()) - 1;
    for (unsigned long i = 0; i < (str.size() / 2); i++) { //reverse the string
        std::swap(str[i], str[n]);
        n = n - 1;
    }
    if (isNegative == true) {
        str.insert(str.begin(), '-');
    }
    


    return trim_leading_zeros(str);
}

string multiply(string lhs, string rhs) {
    bool lhsNegative = false;
    bool rhsNegative = false;
    bool isNegative = false;
    if (lhs.at(0) == '-') { //take out negative signs
        lhs.erase(lhs.begin());
        lhsNegative = true;
    }
    if (rhs.at(0) == '-') {
        rhs.erase(rhs.begin());
        rhsNegative = true;
    }
    string str = "";  //create an empty string
    string mult_result = "0";
    int len1 = lhs.length(), len2 = rhs.length();  //calculate difference of length
    int carry = 0;//initial carry
    int result = 0;
    int number = 0;

    for(int i = len2-1; i >=0; i--) {
        for(int j = len1-1; j >=0; j--) {
            result = digit_to_decimal(lhs.at(j)) * digit_to_decimal(rhs.at(i)) + carry;
            carry = 0;
            if (result > 9) {
                str.insert(str.begin(),decimal_to_digit(result % 10));
                carry = result / 10;
            }
            else {
                str.insert(str.begin(),decimal_to_digit(result));
            }
            result = 0;
        }
        if (carry != 0) {
            str.insert(str.begin(),decimal_to_digit(carry));
            carry = 0;
        }
        for (int k = 0; k < number;k++) {
            str.append("0");
        }
        number++;
        mult_result = add(mult_result, str);
        str = "";

    }
    if ((lhsNegative == false && rhsNegative == true) || (lhsNegative == true && rhsNegative == false)) {
        isNegative = true;
    }
     if (isNegative == true) {
        mult_result.insert(mult_result.begin(), '-');
    }
    return mult_result;


}
