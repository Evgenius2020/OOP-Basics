#include <unordered_map>

namespace Trit_Set {
	enum Trit { False = 0, Unknown = 1, True = 2};
	class TritSet {
	public:
		TritSet(int start_size); // Construcror.
		~TritSet(); // Destrucror.
		Trit& operator[](int i); // Index operator.
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
}