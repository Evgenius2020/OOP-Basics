#include "trit_set.h"
#include "trit.h"
#include "iostream"

typedef unsigned int uint;

namespace Trit_Set 	size_t TritSet::calculate_int_index(int trit_index) {
		return trit_index * 2 / 8 / sizeof(uint);
	}

	TritSet::TritSet(int start_size) : start_size(start_size), curr_size(start_size) {
		int data_length = TritSet::calculate_int_index(start_size - 1) + 1;
		data = new int[data_length];
		for (int i = 0; i < data_length; i++) {
			data[i] = 0;
		}
	}

	TritSet::~TritSet() {
		delete[] data;
	}

	TritContainer TritSet::operator[](int index) {
		return TritContainer(this, index);
	}

	int TritSet::capacity() {
		return TritSet::calculate_int_index(this->curr_size) + 1;
	}

	void TritContainer::modify_trit_value(int* source_int, int trit_position, Trit new_value) {
		unsigned int left_part = *source_int;
		left_part >>= (sizeof(int) * 8 - trit_position) - 2;
		left_part >>= 2; // Stupid, but 'left_part >> sizeof(int)' doing nothing
		left_part <<= 2;
		left_part |= (int)new_value; // 00, 01, 10
		left_part <<= sizeof(int) * 8 - (trit_position + 2);
		
		unsigned int right_part = *source_int;
		right_part <<= trit_position * 2 + 2;
		right_part >>= trit_position * 2 + 2;

		*source_int = left_part | right_part;
	}

	Trit TritContainer::get_trit_value(int source_int, int trit_position) {
		source_int >>= (sizeof(int) * 8 - trit_position) - 2;
		source_int &= 0b11;
		return (Trit)source_int;
	}

	TritContainer::TritContainer(TritSet* trit_set, int index)
		: index(index), trit_set(trit_set) {}

	bool TritContainer::operator==(Trit trit) const{
		int source_int = this->trit_set->data[TritSet::calculate_int_index(this->index)];
		int trit_position = (this->index*2) % (sizeof(int) * 8);
		return TritContainer::get_trit_value(source_int, trit_position) == trit;
	}

	Trit TritContainer::operator=(Trit trit) {
		if (this->index > trit_set->curr_size) {
			if (trit == Trit::Unknown) { // Need to alloc additional memory?
				return Trit::Unknown;
			}
			size_t new_size = TritSet::calculate_int_index(this->index) + 1;
			if (new_size > this->trit_set->capacity()) {
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
			}
			this->trit_set->curr_size = this->index + 1;
		}
		int* source_int = &this->trit_set->data[TritSet::calculate_int_index(this->index)];
		int trit_position = (this->index * 2) % (sizeof(int) * 8);
		modify_trit_value(source_int, trit_position, trit);

		return trit;
	}
}