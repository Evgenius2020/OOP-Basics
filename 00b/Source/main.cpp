#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "sortStrings.h"

using namespace std;

void main(int argc, char* argv[]) {
	list<string> strings;
	list<string>::iterator it = strings.begin();
	
	ifstream input;
	input.open(argv[1], ifstream:: end);
	ofstream output;
	output.open(argv[2], ofstream::out);

	while (!input.eof()) {
		string newString;
		getline(input, newString);
		strings.insert(it, newString);
	}

	SortStrings::sortStrings(strings);

	it = strings.begin();
	while (it != strings.end()) {
		output << *it << endl;
		it++;
	}

	input.close();
	output.close();
}