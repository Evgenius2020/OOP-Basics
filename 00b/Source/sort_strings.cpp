#include <string>
#include <list>
#include "sort_strings.h"

using namespace std;

bool compare_strings(const string& first, const string& second) {
	unsigned int i = 0;
	while ((i < first.length()) && (i < second.length())) {
		if (first[i] < second[i]) {
			return true;
		}
		else if (first[i] > second[i]) {
			return false;
		}
		i++;
	}
	return (first.length() < second.length());
}

list<string> SortStrings::sort_strings(list<string> strings) {
	strings.sort(compare_strings);
	return strings;
}