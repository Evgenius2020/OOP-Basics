#include <map>
#include <string>

namespace GameOfLifeModel {
	static class MatrixSerializator {
		static std::string Serialize(const int** matrix, const std::map<int, char> serializationRule);
		static int** Deserialize(const std::string str, const std::map<char, int> deserializationRule);
	};
}