#include <unordered_map>
#include "trit.h"

namespace Trit_Set {
	class TritSet {
	private:
		int* data;
		int start_size;
		int curr_size;
		friend class TritContainer;
		static size_t calculate_int_index(int trit_index);
	public:
		 TritSet(int start_size); // Construcror.
		 ~TritSet(); // Destrucror.
		TritContainer operator[](int i); // Index operator.
		//TritSet operator&(TritSet set); // AND operator.
		//TritSet operator|(TritSet set); // OR operator.
		//TritSet operator~(); // NOT operator.
		int capacity(); // Returns length of internal array.
		//size_t cardinality(Trit value); // Returns count of trits with 'value' state.
		//std::unordered_map<Trit, int, std::hash<int>> cardinality(); // Returns map with numbers of trits for each possible states.
		//size_t length(); // (Index of last trit with 'False' or 'True' state) + 1.
		//void shrink(); // Reduces length of trits array to 'start_size' or 'length()', if it's bigger than 'start_size.
		//void trim(size_t lastIndex); // Sets all trits since 'lastindex' index in 'Unknown' state.
	};

	class TritContainer {
	private:
		TritSet* trit_set;
		int index;
		void modify_trit_value(int* source_int, int trit_position, Trit new_value);
		static Trit get_trit_value(int source_int, int trit_position);
	public:
		TritContainer(TritSet* trit_set, int index);
		bool operator==(Trit trit) const;
		//bool operator==(TritContainer trit_container);
		Trit operator=(Trit trit);
	};
}