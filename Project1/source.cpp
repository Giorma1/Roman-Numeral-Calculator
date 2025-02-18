#include <iostream>
#include <limits>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

// Roman numerals vecotor and map, What map doing is, You can set integer value to string and string value to integer, So we ar checking roman numerals in map as string and taking its value in integer.
vector<pair<int, string>> int_to_roman = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};
map<char, int> roman_to_int = { {'M', 1000}, {'D', 500}, {'C', 100}, {'L', 50}, {'X', 10}, {'V', 5}, {'I', 1}, };
// Roman to integer
int roman_to_numeral(string num1) {

    int result = 0;

    /* Here we're translforming roman to integer, In for loop we are counting the characters in user input(in roman),
    in if statment, If (i + 1 < num1.length() in here we're checking if there is more than one character, i = 0 + 1, i = 1,
    if we get IX as input num1.length() will be 2, So 1<2 and it will be true.
    and roman[num1[i]] < roman[num1[i + 1]] here we're comparing the first character and second character in input, roman[num1[i]] is same as "I" and roman[num1[i + 1] is "X
    if we get IX as input, And we are comparing its values in integer in roman hash map like this.
    so what this doing is roman[num1[i]] < roman[num1[i + 1]], if I < X we will do subtract, And result = 0 - 1, result = -1,
    And after next loop there will be only X only one character
    and if statement will return false and make the else statment, Remembre result = -1, And after we add a 10 to -1 we get 9, so result = 9.
    */
    for (int i = 0; i < num1.length(); i++) {
        if (i + 1 < num1.length() && roman_to_int[num1[i]] < roman_to_int[num1[i + 1]]) {
            result -= roman_to_int[num1[i]];
        }
        else {
            result += roman_to_int[num1[i]];
        }
    }

    return result;

}

// Integer to roman
string numeral_to_roman(int num1) {
    string result = "";

    for (auto i : int_to_roman) {
        while (num1 >= i.first) {
            result += i.second;
            num1 -= i.first;
        }
    }

    return result;
}

// Input validation function
bool is_valid_roman(const string& s) {
    // Check if all characters are valid
    for (char c : s) {
        if (roman_to_int.find(c) == roman_to_int.end()) {
            return false;
        }
    }

    // Check repetition rules
    for (size_t i = 0; i < s.length(); i++) {
        char current = s[i];
        int count = 1;

        // Count consecutive occurrences of the same character
        while (i + 1 < s.length() && s[i + 1] == current) {
            count++;
            i++;
        }

        // Check if the repetition is valid
        if ((current == 'V' || current == 'L' || current == 'D') && count > 1) {
            return false; // V, L, D cannot be repeated
        }
        if ((current == 'I' || current == 'X' || current == 'C' || current == 'M') && count > 3) {
            return false; // I, X, C, M cannot be repeated more than 3 times
        }
    }

    // Check subtractive notation and order of characters
    for (size_t i = 0; i + 1 < s.length(); i++) {
        int current_value = roman_to_int[s[i]];
        int next_value = roman_to_int[s[i + 1]];

        // If current character is smaller than the next, it must be a valid subtractive pair
        if (current_value < next_value) {
            if (!((current_value == 1 && (next_value == 5 || next_value == 10)) ||   // I before V or X
                (current_value == 10 && (next_value == 50 || next_value == 100)) || // X before L or C
                (current_value == 100 && (next_value == 500 || next_value == 1000)))) { // C before D or M
                return false;
            }
        }
    }

    return true;
}

// Calculation with switch statment
string calculator(int num1, int num2, char opera) {
    int sum;
    switch (opera)
    {
    case '*':
        sum = num1 * num2;
        return numeral_to_roman(sum);
        
    case '/':
        sum = num1 / num2;
        return numeral_to_roman(sum);

    case '-':
        sum = num1 - num2;
        return numeral_to_roman(sum);

    case '+':
        sum = num1 + num2;
        return numeral_to_roman(sum);

    default:
        return "invalid Input";
    }

}



// Asking function
void asking() {

    char again = 'y';
    char oper;
    string num1, num2;

    // Asking user start or not at start
    cout << "Start? y/n: ";
    cin >> again;

    // While user inputs y or Y program keeps going, If inputs anything other it will stop.
    while (again == 'y' or again == 'Y') {

        // Asking user to input first number
        while (true) {

            cout << "Enter First Roman Number: ";
            cin >> num1;
            transform(num1.begin(), num1.end(), num1.begin(), ::toupper);
            if (is_valid_roman(num1)){
                break;
            }
            else {
                cout << "invalid Input, Please Enter numeral. \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            }

        }

        // Asking user to input operator
        while (true) {

            cout << "Enter Operator: '+', '-', '*', '/'. ";
            cin >> oper;
            if (oper == '+' or oper == '-' or oper == '*' or oper == '/') {
                break;
            }
            else {
                cout << "invalid operator please try again \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Asking user to input second number
        while (true) {

            cout << "Enter Second Roman Number: ";
            cin >> num2;
            transform(num2.begin(), num2.end(), num2.begin(), ::toupper);
            if (is_valid_roman(num2)) {
                break;
            }
            else {
                cout << "invalid Input, Please Enter numeral. \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        // Printing calculator function with num1 and num2 inputs in roman numeral but calculator function takes them as integer with roman_to_numeral function.
        cout << calculator(roman_to_numeral(num1), roman_to_numeral(num2), oper) << "\n";

        // Asking to start again or not after the calculation.
        cout << "Start again? y/n: ";
        cin >> again;

    }

    
    }


int main() {
    
    asking();
    
}