#include "trit_set.h"
#include "trit_container.h"
#include "trit.h"

namespace Trit_Set {
	size_t TritSet::calculate_int_index(int trit_index) {
		return trit_index * 2 / 8 / sizeof(int);
	}

	TritSet::TritSet(int start_size) : start_size(start_size), curr_size(start_size) {
		int data_length = TritSet::calculate_int_index(start_size - 1);
		data = new int[data_length];
		for (int i = 0; i < data_length; i++) {
			data[i] = 0;
		}
	}

	TritSet::~TritSet() {
		delete[] data;
	}

	TritContainer TritSet::operator[](int index)
	{
		return TritContainer(this, index);
	}

	int TritSet::capacity() {
		return curr_size / sizeof(int);
	}

	TritContainer::TritContainer(TritSet* trit_set, int index) 
		: index(index), trit_set(trit_set) {}

	Trit TritContainer::operator=(Trit trit) {
		if (this->index >= trit_set->curr_size) {
			if (trit == Trit::Unknown) { // Need to alloc additional memory?
				return Trit::Unknown;
			}
			size_t new_size = TritSet::calculate_int_index(this->index - 1);
			int* new_data = new int[new_size];
			// TODO: Simplier pls
			for (int i = 0; i < this->trit_set->curr_size; i++) {
				new_data[i] = trit_set->data[i];
			}
			for (int i = this->trit_set->curr_size; i < new_size; i++) {
				new_data[i] = 0;
			}
			delete this->trit_set->data;
			this->trit_set->data = new_data;
			this->trit_set->curr_size = new_size;
		}
		int* source_int = &this->trit_set->data[TritSet::calculate_int_index(this->index)];
		int trit_position = this->index % (sizeof(int) * 8);
		modify_trit_value(source_int, trit_position, trit);

		return trit;
	}
}