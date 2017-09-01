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
	input.open(argv[1], ifstream::beg);
	ofstream output;
	output.open(argv[2], ofstream::out);

	while (!input.eof()) {
		string newString;
		getline(input, newString);
		strings.insert(it, newString);
	}

	strings = SortStrings::sortStrings(strings);

	if (strings.size() > 0) {
		for (it = strings.begin(); it != strings.end(); it++) {
			output << *it << endl;
		}
	}

	input.close();
	output.close();
}