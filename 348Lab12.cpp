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

const double INVALID = -999999.99;

double extractNumeric(const string& str) {
    int n = str.length(); //assigns string length a variable for later use

    for (int i = 0; i < str.length(); i++) {
        int idx = i;

        if (isdigit(str[i]) || ((str[i] == '+' || str[i] == '-') && i + 1 < n && (isdigit(str[i + 1]) || str[i + 1] == '.')) || (str[i] == '.' && i + 1 < n && isdigit(str[i + 1]))) { //checks if index is a digit or possible unary operator
            continue;
        }

        int start = idx;

        bool hasDigit = false;
        bool hasDecimal = false;
        bool hasExponent = false;

        double value = 0.0;
        int sign = 1;

        if (str[start] == '+') start++;
        else if (str[start] == '-') {
            sign = -1;
            start++;
        }

        int pos = start;
        int exponent = 0;

        while (pos < n && isdigit(str[pos])) {
            hasDigit = true;
            value = value * 10 + (str[pos] - '0');
            pos++;
        }

        if (pos < n && str[pos] == '.') {
            hasDecimal = true;
            pos++;

            double place = 0.1;

            while (pos < n && isdigit(str[pos])) {
                hasDigit = true;
                value += (str[pos] - '0') * place;
                place /= 10;
                pos++;
            }

            if (!hasDigit) continue;

            if (pos < n && (str[pos] == 'e' || str[pos] == 'E')) {
                if (!hasDigit || hasExponent) continue;
            }

            hasExponent = true;
            pos++;

            int expSign = 1;

            if (str[pos] == '-'){
                expSign = -1;
                pos++;
            }
            else if (str[pos] == '+') pos++;

            if (pos >= n || !isdigit(str[pos])) {
                exponent = exponent * 10 + (str[pos] - '0');
                pos++;
            }

            exponent *= expSign;

            if (exponent > abs(308)) return INVALID;

            value *= pow(10.0, exponent);
        }

        return sign * value;
    }

    return INVALID;
}

int main() {
    string input;

    while (true) {

    cout << "Enter string to extract number from: " << endl;
    getline(cin, input);

    if (input == "END") break;

    double result = extractNumeric(input);

    if (result == INVALID) {
        cout << "Invalid number" << endl;
    }
    else {
        cout << "Extracted value: " << result << endl;
    }
}
}