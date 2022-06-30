#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {

    string leftHand = "";
    string op = "";
    string rightHand = "";
    string result = "";

    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    while((leftHand != "q") || (leftHand != "quit")) {
        cout << ">> ";

        cin >> leftHand;

        if(leftHand == "q" || leftHand == "quit") {
            cout << endl;
            break;
        }
        cin >> op;
        cin >> rightHand;

        cout << endl;

        if(op == "+") {
            result = add(leftHand, rightHand);
        } else if(op == "*") {
            result = multiply(leftHand, rightHand);
        }
        cout << "ans =" << endl << endl;
        cout << "    " << result << endl << endl;
    }
    cout << "farvel!" << endl << endl;
}

