//Name: Maddi Clark
//ID: 3162616
//Date: 05/08/2026
//Description: extracts numbers from an inputted string of text
//Inputs: a string of garbage characters with a number to be extracted
//Outputs: the extracted number
//Sources: Chatgpt, "How should I tackle writing a number extractor that extracts numbers from a long string of random characters" to get a basic idea of framework and implementation order

#include <iostream> //Allows for input and output streams
#include <string> //Allows the use of string data type
#include <cctype> //Allows for functions isdigit() and isalpha()
#include <cmath> //Allows for math function pow()

using namespace std;

double extractNumeric(const string& str) {
    int n = str.length(); //assigns string length a variable for later use

    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i]) || str[i] == '+' || str[i] == '-' || str[i] == '.') { //checks if index is a digit or possible unary operator
            if ((str[i] == '+' || str[i] == '-')) {
                if (i + 1 >= n){ //checks if a sign is at the end of the string
                    continue;

                if (!isdigit(str[i + 1]) && str[i + 1] != '.') { //checks if the sign is followed by a non-digit that isnt a decimal point
                    continue;
                }
            }

            int j = i;

            while (j < n && (isdigit(str[j]) || str[j] == '+' || str[j] == '-' || str[j] == '.' || str[j] == 'e' || str[j] == 'E')) { 
                j++; //increments j for as long as it is less than the length of the string and is a possible piece of a number
            }

            string token == str.substr(i, j-i); //creates a substring for as long as the potential number is

            int pos = 0;

            bool hasDigit = false;
            bool hasDecimal = false;
            bool hasExponent = false;

            if (token[pos] == '+' || token[pos] == '-'){
                pos++; //current position incremented if there's a leading sign
            }

            if (pos >= token.length()) return INVALID; //current position cannot be past the length of substring

            while (pos < token.length()) {
                char c = token[pos]; //creates a copy of the current character in the substring being evaluated

                if (isdigit(c)) {
                    hasDigit = true; //marks that the char at current position is a digit, so the substring has a digit
                    pos++;
                }

                else if (c == '.') {
                    if (hasDecimal || hasExponent) return INVALID; //a number cannot have two decimals or have an exponent before the decimal

                    hasDecimal == true; //marks that the substring has a decimal and increments position
                    pos++
                }

                else if (c == 'e' || c == 'E') {
                    if (hasExponent || !hasDigit) return INVALID; //cannot take the exponent without a digit beforehand, also cannot have multiple exponents

                    hasExponent = true;
                    pos++;

                    if (pos < token.length() && (token[pos] == '+' || token[pos] == '-')) { //allows for the exponent to have a sign
                        pos++;
                    }

                    int expDigits = 0;

                    while (pos < token.length() && isdigit(token[pos])) {
                        expDigits++;
                        pos++
                    }

                    if (expDigits == 0) return INVALID; //Cannot take the exponent of nothing

                    break;
                }

                else {
                    return INVALID;
                }

                if (!hasDigit) return INVALID; //Number must contain at least one digit
            }
        }
    }
}

void main() {
    string input;

    cout << "Enter string to extract number from: " << endl;
    getline(cin, input)

    double result = extractNumeric(input);

    if (result == INVALID) {
        cout << "Invalid number" << endl;
    }
    else {
        cout << "Extracted value" << result << endl;
    }
}