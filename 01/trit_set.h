#include <unordered_map>

namespace trit_set {
	enum Trit { False, Unknown, True };
	class Trit_Set {
	public:
		Trit_Set(int size);
		Trit operator[](int i);
		Trit_Set operator&(Trit_Set set);
		Trit_Set operator|(Trit_Set set);
		Trit_Set operator~();
		int capacity();
		size_t cardinality(Trit value);
		std::unordered_map<Trit, int, std::hash<int>> cardinality();
		void shrink();
		void trim(size_t lastIndex);
		size_t length();
	};
}