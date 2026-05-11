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

const double INVALID = -999999.99; //creates a constant value to output in case of invalid inputs

double extractNumeric(const string& str) {
    int n = str.length();

    for (int i = 0; i < n; i++) { //runs for as long as the input string is

        //checks for the start of the number by checking for any possible pieces of a number
        bool validStart = isdigit(str[i]) || ((str[i] == '+' || str[i] == '-') && i + 1 < n && (isdigit(str[i + 1]) || str[i + 1] == '.')) || (str[i] == '.' && i + 1 < n && isdigit(str[i + 1]));

        if (!validStart) continue;

        int start = i; //sets start of the number to the current index

        bool hasDigit = false;

        double value = 0.0; //value to be added to later
        int sign = 1; //sets whether sign is positive or negative

        if (str[start] == '+') start++;
        else if (str[start] == '-') {
            sign = -1; //if the beginning of the number is a minus sign, sets sign to -1 to be multiplied by at the end
            start++;
        }

        int pos = start; //creates a copy of where start is to be used as we continue

        int decimalCount = 0; //decimal count to ensure there is no more than one decimal in a number
        int digitCount = 0; //counts digits so that a string such as '99999999999999999999' is invalid

        while (pos < n && isdigit(str[pos])) { //checks digit count of the string and makes sure the value is within range

            digitCount++;

            if (digitCount > 18) return INVALID;

            int digit = str[pos] - '0';

            if (value > (1e308 - digit) / 10.0) return INVALID;

            hasDigit = true;
            value = value * 10 + digit;
            pos++;
        }

        if (pos < n && str[pos] == '.') {

            decimalCount++;

            if (decimalCount > 1) return INVALID; //rejects numbers with multiple decimals

            pos++;

            double place = 0.1;

            while (pos < n && isdigit(str[pos])) { //adds decimal value to value
                hasDigit = true;
                value += (str[pos] - '0') * place;
                place /= 10;
                pos++;
            }

            if (pos < n && str[pos] == '.') { //checks for an extra decimal point
                return INVALID;
            }
        }

        if (!hasDigit) continue;

        if (pos < n && (str[pos] == 'e' || str[pos] == 'E')) { //checks for exponents

            pos++;

            int expSign = 1;

            if (pos < n && str[pos] == '-') { //allows for negative exponents
                expSign = -1;
                pos++;
            }
            else if (pos < n && str[pos] == '+') {
                pos++;
            }

            int exponent = 0;

            if (pos >= n || !isdigit(str[pos])) { //rejects non-digit exponents
                return INVALID;
            }

            while (pos < n && isdigit(str[pos])) { //adds to the exponent for as long as there are digits after the e
                exponent = exponent * 10 + (str[pos] - '0');
                pos++;
            }

            exponent *= expSign; //multiplies exponent by its sign so it can be negative

            if (abs(exponent) > 308) { //rejects exponents out of range
                return INVALID;
            }

            value *= pow(10.0, exponent); //fulfills the exponent
        }

        if (abs(value) > 1e308) { //rejects values outside of range
            return INVALID;
        }

        return sign * value; //multiplies the value by its sign in case it's negative
    }

    return INVALID; //returns invalid in case the string contains no number
}

int main() {
    string input;

    while (true) { //keeps loop running until end is entered

    cout << "Enter a string (or 'END' to quit): " << endl;
    getline(cin, input);

    if (input == "END") { //breaks loop when end is entered
        cout << "Program terminated." << endl;
        break;
    }

    double result = extractNumeric(input);

    if (result == INVALID) {
        cout << "Invalid input: no valid floating-point number found" << endl;
    }
    else {
        cout << "Extracted number: " << result << endl;
    }
}
}