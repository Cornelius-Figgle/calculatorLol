#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

//________________________________________________________________________________________________________________________________

int i; //:loops etc

string line; //:equation input
string item; //:splitting equation

vector<string> arr; //:split equation
vector<double> numArr; //:numbers in equation
map<string, string> arrMapping; //:map arr elements to types
vector<int> equatorialLocations; //:maths

vector<string> recog; //:determined fn()
vector<string> errorList; //:reporting errors
string msg; //:error reporting

double ans; //:maths

void convertToVector(vector<string> &arr);
string determineSegments(map<string, string> &arrMapping, vector<double> &numArr, vector<int> &equatorialLocations);
void solveEquation(double &ans);
int main();

//________________________________________________________________________________________________________________________________

void convertToVector(vector<string> &arr) {
	i = 0;
	cout << '\n';
	line.append(" "); //so program sees eol as space b/c I dont know codes for eol/eof (I guess just check for '\r\n' or '\n' but oh well)
	while (i <= line.length()) { 
		if (line[i] != ' ') { //if not end of item
			item = item + line[i]; //builds up
			cout << "iter '" << i << "' | char '" << line[i] << "' | item '" << item << "'" << '\n';
		} else { //space
			arr.push_back(item); //append to vector
			cout << "iter '" << i << "' | char '" << line[i] << "' | item '" << item << "'" << " | br" << '\n';

			item = ""; //reset item
		} 
		i++; //increase
	}

	cout << '\n';
	for (auto val: arr) { //checks values are correct
		cout << "val '" << val << "' " << '\n';
	}
}

string determineSegments(map<string, string> &arrMapping, vector<double> &numArr, vector<int> &equatorialLocations) {
	i = 0;
	cout << '\n';
	for (auto val: arr) { //for val in arr:
		if ((strspn(val.c_str(), "-.0123456789" ) == val.size()) == true) { //if it's a number
			try { //try to convert to num
				numArr.push_back(stod(val)); //converts to double then appends to numArr

				arrMapping["arr[" + to_string(i) + "]"] = "dbl"; //write type to map

				vector<double>::iterator itr = find(numArr.begin(), numArr.end(), stod(val)); //get location of val in numArr

				if (itr != numArr.cend()) { 
					equatorialLocations.push_back(distance(numArr.begin(), itr)); //add this to vector
				} else {
					return errorList[0];
				}

				cout << "iter '" << i << "' | val '" << val << "' | type '" << arrMapping["arr[" + to_string(i) + "]"] << "' | numArr loc '" << distance(numArr.begin(), itr) << "'" << '\n';

			} catch (...) { //if it is part of num but not convertable (ie '-')
				arrMapping["arr[" + to_string(i) + "]"] = "str"; //write type to map

				vector<string>::iterator itr = find(recog.begin(), recog.end(), val); //get location of val in recog

				if (itr != recog.cend()) { 
					equatorialLocations.push_back(distance(recog.begin(), itr));
				} else {
					return errorList[1] + "(check val: " + val + ")";
				}

				cout << "iter '" << i << "' | val '" << val << "' | type '" << arrMapping["arr[" + to_string(i) + "]"] << "' | recog loc '" << distance(recog.begin(), itr) << "'" << '\n';
			}
		} else { //if its a symbol or smth
			arrMapping["arr[" + to_string(i) + "]"] = "str"; //write type to map

			vector<string>::iterator itr = find(recog.begin(), recog.end(), val); //get location of val in recog

			if (itr != recog.cend()) { 
				equatorialLocations.push_back(distance(recog.begin(), itr));
			} else {
				return errorList[1] + "(check val: " + val + ")";
			}

			cout << "iter '" << i << "' | val '" << val << "' | type '" << arrMapping["arr[" + to_string(i) + "]"] << "' | recog loc '" << distance(recog.begin(), itr) << "'" << '\n';
		}
		i++;
	}
	return ""; 
}	

void solveEquation(double &ans) {
	cout << '\n';
	
	i = 0;
	while (arrMapping["arr[" + to_string(i) + "]"] != "str") { //looks for a symbol
		i++;
	}
	switch (equatorialLocations[i]) { //work out where the first number is regarding that symbol
		case 0:
			ans = numArr[equatorialLocations[i - 1]]; //cache initial answer
			break;
		case 1:
			ans = numArr[equatorialLocations[i - 1]];
			break;
		case 2:
			ans = numArr[equatorialLocations[i - 1]];
			break;
		case 3:
			ans = numArr[equatorialLocations[i - 1]];
			break;
		case 4:
			ans = numArr[equatorialLocations[i - 1]];
			break;
	} cout << "ans '" << ans << "'" << '\n';

	i = 0;
	for (i; i <= equatorialLocations.size(); i++) { //for items
		if (arrMapping["arr[" + to_string(i) + "]"] == "str") { //look for symbol
			switch (equatorialLocations[i]) { //work out equation based on symbol
				case 0:
					ans = ans + numArr[equatorialLocations[i + 1]];
					cout << "ans '" << ans << "'" << '\n';
					break;
				case 1:
					ans = ans - numArr[equatorialLocations[i + 1]];
					cout << "ans '" << ans << "'" << '\n';
					break;
				case 2:
					ans = ans * numArr[equatorialLocations[i + 1]];
					cout << "ans '" << ans << "'" << '\n';
					break;
				case 3:
					ans = ans / numArr[equatorialLocations[i + 1]];
					cout << "ans '" << ans << "'" << '\n';
					break;
				case 4:
					ans = pow (ans, numArr[equatorialLocations[i + 1]]);
					cout << "ans '" << ans << "'" << '\n';
					break;
			}
		}
	}
}

int main() {
	recog = {"+", "-", "*", "/", "^", " "};
	errorList = {"internal error: num from arr not in numArr (possible conversion error?)", "not a symbol (unrecognised)"};

	cout << "\n\tEnter your equation: ";
	getline(cin, line);

	convertToVector(arr);
	msg = determineSegments(arrMapping, numArr, equatorialLocations);
	if (msg != "") {
		cout << '\n' << msg << '\n';
		_getch();
		return EXIT_FAILURE;
	}
	solveEquation(ans);
	cout << "\n\t" << ans;

	cout << "\n\n"; 
	_getch(); //so no auto close when exe b/c read
	return EXIT_SUCCESS;
}