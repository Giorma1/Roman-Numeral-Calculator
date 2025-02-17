#include <iostream>
#include <limits>
#include <map>
#include <algorithm>

using namespace std;

// operation functions from here

int add(int num1, int num2) {
	return num1 + num2;
}

int subtract(int num1, int num2) {
	return num1 - num2;
}

int divide(int num1, int num2) {
	return num1 / num2;
}

int multiply(int num1, int num2) {
	return num1 * num2;
}
// to here

// calculation with switch statment
int calculator(int num1, int num2, char opera) {
	switch (opera)
	{
	case '*':
		return multiply(num1, num2);
	
	case '/':
		return  divide(num1, num2);

	case '-':
		return subtract(num1, num2);

	case '+':
		return add(num1, num2);

	default:
		return 0;
	}

}

int roman_to_numeral(string num1) {

	// roman numerals hash map, what hash map doing is, you can set integer value to string and string value to integer, so we ar checking roman numerals in hash map as string and taking its value in integer.
	map<char, int> roman = { {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000} };

	int result = 0;

	/* here we're translforming roman to integer, in for loop we are counting the characters in user input(in roman), 
	in if statment, if (i + 1 < num1.length() in here we're checking if there is more than one character, i = 0 + 1, i = 1, 
	if we get IX as input num1.length() will be 2, so 1<2 and it will be true.
	and roman[num1[i]] < roman[num1[i + 1]] here we're comparing the first character and second character in input, roman[num1[i]] is same as "I" and roman[num1[i + 1] is "X
	if we get IX as input, and we are comparing its values in integer in roman hash map like this.
	so what this doing is roman[num1[i]] < roman[num1[i + 1]], if I < X we will do subtract, and result = 0 - 1, result = -1,
	and after next loop there will be only X only one character
	and if statement will return false and make the else statment, remembre result =-1, and after we add a 10 to -1 we get 9, so result = 9.
	*/
	for (int i = 0; i < num1.length(); i++) {
		if (i + 1 < num1.length() && roman[num1[i]] < roman[num1[i + 1]]) {
			result -= roman[num1[i]];
		}
		else {
			result += roman[num1[i]];
		}
	}

	return result;

}

// asking function
void asking() {

	char again = 'y';
	char oper;
	string num1, num2;

	// asking user start or not at start
	cout << "Start? y/n: ";
	cin >> again;

	// while user inputs y or Y program keeps going, if inputs anything other it will stop.
	while (again == 'y' or again == 'Y') {

		// asking user to input first number
		while (true) {

			cout << "Enter First Roman Number: ";
			cin >> num1;
			if (num1.length() <= 4){
			break;
			}
			else {
				cout << "invalid Input, Please Enter numeral. \n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

			}

		}

		// asking user to input operator
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

		// asking user to input second number
		while (true) {

			cout << "Enter Second Roman Number: ";
			cin >> num2;
				if (num2.length() <= 4) {
					break;
				}
			else {
				cout << "invalid Input, Please Enter numeral. \n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		// printing calculator function with num1 and num2 inputs in roman numeral but calculator function takes them as integer with roman_to_numeral function.
		cout << calculator(roman_to_numeral(num1), roman_to_numeral(num2), oper) << "\n";

		// asking to start again or not after the calculation.
		cout << "Start again? y/n: ";
		cin >> again;

	}

	
	}


int main() {

	asking();
	
}