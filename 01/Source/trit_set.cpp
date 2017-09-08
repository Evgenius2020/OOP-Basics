#include "trit_set.h"

namespace Trit_Set {
	class TritSet {
		int* data;
		int start_size;
		int curr_size;
	public:
		TritSet(int start_size) : start_size(start_size), curr_size(start_size) {
			int dataLength = start_size * 2 / 8 / sizeof(int);
			data = new int[dataLength];
			for (int i = 0; i < curr_size; i++) {
				data[i] = Trit::Unknown;
			}
		}

		~TritSet() {
			delete[] data;
		}

		Trit& operator[](int i) {
			Trit* result = new Trit;
			if (i >= curr_size) {
				*result = Trit::Unknown;
			}
			else {
				int partIndex = i / sizeof(int);
				*result = (Trit)((data[partIndex] >> 2 * (i % 4)) & 0b11);
			}
			return *result;
		}

		int capacity() {
			return curr_size / sizeof(int);
		}
	};

}