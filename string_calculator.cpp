#include <iostream>
#include <string>
#include "./string_calculator.h"
#include <sstream>
#include <limits>

using std::cout, std::endl;
using std::string;


/*
convert a character digit to an integer value
input: digit - a character representing a digit, e.g. '7'
output: the corresponding integer value of the digit, e.g. 7
throws: std::invalid_argument if the input is not a valid digit, e.g. '0' -- '9'
*/
unsigned int digit_to_decimal(char digit) {
    if(isdigit(digit)) {
        int dec = (int)digit - 48;
        return dec;
    } else {
        throw std::invalid_argument("Invalid digit!");
    }
    return 0;
}

/*
convert an integer value to a character digit
input: decimal - an integer value of a digit, e.g. 7
output: the corresponding character of the digit, e.g. '7'
throws: std::invalid_argument if the input is not a valid digit, e.g. 0 -- 9
*/
char decimal_to_digit(unsigned int decimal) {
    if((decimal == 0) || (decimal == 1) || (decimal == 2) || (decimal == 3) || (decimal == 4) || (decimal == 5) || (decimal == 6) || (decimal == 7) || (decimal == 8) || (decimal == 9)) {
        char res = decimal + '0';
        return res;
    } else {
        throw std::invalid_argument("Invalid dec!");
    }
    return '\0';
}

/*
remove the leading zeros from a number
input: num - a string representing a number with zero or more leading 0s
output: a copy of the input with all leading 0s removed
throws: none 
*/
string trim_leading_zeros(string num) {
    // iterates through each digit to check for '0' as the value

    // postive numbers

    unsigned int len = num.length() - 1;

    if((num[0] == '-') || (num[0] == '0')) {
        if(num[0] == '0') {
            for(unsigned int i = 0; i <= len; i++) {
                if(num[0] != num[i]) {
                    num = num.substr(i, num.length() - i);
                    return num;
                }
            }
        } else if(num[0] == '-') {
            for(unsigned int i = 1; i <= len; i++) {
                if(num[i] != '0') {
                    num = num[0] + num.substr(i, num.length() - i);
                    return num;
                }
            }
        }
    } else {
        return num;
    } 
    return "0";
} 


/*
add two numbers 
input: lhs,rhs - strings representing numbers, e.g. "1", "2"
output: the result of adding rhs to lhs: lhs + rhs e.g. "3"
throws: none.
*/
string add(string lhs, string rhs) {
    int addlhs = 0;
    int addrhs = 0;
    int length = 0;
    int carry = 0;
    int sub = 0;
    int tempNum = 0;
    string totalNum = "";
    string totalAdd = "";

    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    if(rhs.length() < lhs.length()) {
        length = lhs.length();
        sub = length - rhs.length();

        if(rhs[0] != '-') {
            rhs = rhs.insert(0, sub, '0');
        } else {
            rhs = rhs.insert(1, sub, '0');
        }
    } else if(rhs.length() > lhs.length()) {
        length = rhs.length();
        sub = length - lhs.length();

        if(lhs[0] != '-') {
            lhs = lhs.insert(0, sub, '0');
        } else {
            lhs = lhs.insert(1, sub, '0');
        }
    } else {
        length = lhs.length();
    }

    if(lhs[0] != '-') {
        for(int i = length - 1; i >= 0; i--) {
            addlhs = digit_to_decimal(lhs[i]);
            addrhs = digit_to_decimal(rhs[i]);
            tempNum = addlhs + addrhs + carry;

            if(tempNum >= 10) {
                carry = 1;
                tempNum = tempNum - 10;
            } else {
                carry = 0;
            }
            tempNum = decimal_to_digit(tempNum);
            totalNum.push_back(tempNum);

            if((carry == 1) && (i == 0)) {
                totalNum = totalNum + "1";
            }
        }

        for(int i = totalNum.length() - 1; i >= 0; i--) {
            totalAdd.push_back(totalNum[i]);
        }
    } else if(lhs[0] == '-') {
        for(int i = length - 1; i >= 1; i--) {
            addlhs = digit_to_decimal(lhs[i]);
            addrhs = digit_to_decimal(lhs[i]);
            tempNum = addlhs + addrhs + carry;

            if(tempNum >= 10) {
                carry = 1;
                tempNum = tempNum - 10;
            } else {
                carry = 0;
            }
            tempNum = decimal_to_digit(tempNum);
            totalNum.push_back(tempNum);
            
            if((carry == 1) && (i == 1)) {
                totalNum = totalNum + "1";
            }
        }
        for(int i = totalNum.length() - 1; i >= 0; i--) {
            totalAdd.push_back(totalNum[i]);
        }
        totalAdd = '-' + totalAdd;
    }
    return totalAdd;
}

/*
muplity two numbers
input: lhs,rhs - strings representing numbers, e.g. "1", "2"
output: the result of multiplying lhs by rhs: lhs * rhs, e.g. "2"
throws:  none.
*/
string multiply(string lhs, string rhs) {
    
    int prodLhs = 0, prodRhs = 0, len = 0, sub = 0, carry = 0, prod = 0, minusCount = 0;
    string totalProd = "", tempProd = "", pastProd = "";

    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    if((rhs[0] == '-') && (lhs[0] != '-')) {
        minusCount++;
        rhs.erase(0,1);
    }
    if((lhs[0] == '-') && (rhs[0] != '-')) {
        minusCount = 1;
        lhs.erase(0,1);
    }
    if((lhs[0] == '-') && rhs[0] == '-') {
        minusCount = 0;
        lhs.erase(0,1);
        rhs.erase(0,1);
    }

    if(rhs.length() > lhs.length()) {
        len = rhs.length();
        sub = len - lhs.length();
        lhs = lhs.insert(0, sub+1, '0');
        rhs = rhs.insert(0, 1, '0');
    } else if(rhs.length() < lhs.length()) {
        len = lhs.length();
        sub = len - rhs.length();
        lhs = lhs.insert(0, 1, '0');
        rhs = rhs.insert(0, sub+1, '0');
    } else {
        len = lhs.length();
        lhs = lhs.insert(0, 1, '0');
        rhs = rhs.insert(0, 1, '0');
    }

    for(int i = len; i >= 0; i--) {
        prodRhs = digit_to_decimal(rhs[i]);
            for(int j = len; j >= 0; j--) {
                prodLhs = digit_to_decimal(lhs[j]);

                prod = (prodLhs * prodRhs) + carry;

                if((prod != 0) && (prod >= 10)) {
                    carry = prod / 10;
                    prod = prod % 10; 
                } else {
                    carry = 0;
                }
                
                prod = decimal_to_digit(prod);
                pastProd.push_back(prod);

                if(j == 0) {
                    pastProd = pastProd.insert(0, len - i, '0');
                    for(int k = pastProd.length() - 1; k >= 0; k--) {
                        tempProd.push_back(pastProd[k]);
                    }

                    totalProd = add(tempProd, totalProd);
                    pastProd = "";
                    tempProd = "";
                }
            }
        }
        if(minusCount == 1) {
            totalProd = '-' + totalProd;
        }

        return totalProd;
    }
    
