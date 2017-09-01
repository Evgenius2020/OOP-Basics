#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "sort_strings.h"

using namespace std;

void main(int argc, char* argv[]) {
	list<string> strings;
	list<string>::iterator it = strings.begin();

	if (argc != 3) {
		return;
	}
	ifstream input;
	input.open(argv[1], ifstream::beg);
	ofstream output;
	output.open(argv[2], ofstream::out);
	if (input.is_open() && output.is_open()) {
		while (!input.eof()) {
			string newString;
			getline(input, newString);
			strings.insert(it, newString);
		}

		strings = SortStrings::sort_strings(strings);

		if (strings.size() > 0) {
			for (it = strings.begin(); it != strings.end(); it++) {
				output << *it << endl;
			}
		}
	}

	input.close();
	output.close();
}