//Name: Maddi Clark
//ID: 3162616
//Date: 05/08/2026
//Description: extracts numbers from an inputted string of text
//Inputs: a string of garbage characters with a number to be extracted
//Outputs: the extracted number

#include <iostream> //Allows for input and output streams
#include <string> //Allows the use of string data type
#include <cctype> //Allows for functions isdigit() and isalpha()
#include <cmath> //Allows for math function pow()

using namespace std;

double extractNumeric(const string& str) {
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i]) || str[i] == '+' || str[i] == '-' || str[i] == '.') {
            if ((str[i] == '+' || str[i] == '-')) {
                if (i + 1 >= n){
                    continue;
                }

                if (!isdigit(str[i + 1]) && str[i + 1] != '.') {
                    continue;
                }
            }

            int j = i;

            while (j < n && (isdigit(str[j]) || str[j] == '+' || str[j] == '-' || str[j] == '.' || str[j] == 'e' || str[j] == 'E')) {
                j++;
            }
        }
    }
}

void main() {
    extractNumeric(string);
}