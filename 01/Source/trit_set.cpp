#include "trit_set.h"

namespace Trit_Set {
	Trit_Set::TritSet::TritSet(int start_size) : start_size(start_size), curr_size(start_size) {
		int data_length = start_size * 2 / 8 / sizeof(int) + 1;
		data = new int[data_length];
		for (int i = 0; i < data_length; i++) {
			data[i] = Trit::Unknown;
		}
	}

	Trit_Set::TritSet::~TritSet() {
		delete[] data;
	}

	Trit& Trit_Set::TritSet::operator[](int i) {
		Trit* result = new Trit;
		if (i >= curr_size) {
			*result = Trit::Unknown;
		}
		else {
			int part_index = i / sizeof(int);
			int part = (data[part_index] >> (8 - ((i * 2) + 2)) & 0b11);
			*result = (Trit)part;
		}
		return *result;
	}

	int Trit_Set::TritSet::capacity() {
		return curr_size / sizeof(int);
	}
}