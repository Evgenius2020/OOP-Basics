#include <string>
#include <list>
#include "sortStrings.h"

using namespace std;

bool compareStrings(const string& first, const string& second) {
	unsigned int i = 0;
	while ((i < first.length()) && (i < second.length())) {
		if (tolower(first[i]) < tolower(second[i])) {
			return true;
		}
		else if (tolower(first[i]) > tolower(second[i])) {
			return false;
		}
		i++;
	}
	return (first.length() < second.length());
}

list<string> SortStrings::sortStrings(list<string> strings) {
	strings.sort(compareStrings);
	return strings;
}