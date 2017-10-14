#include <map>
#include <string>
#include "CellState.h"

using namespace std;

namespace GameOfLife {
	static class MatrixSerializator {
		static string Serialize(const int** matrix, map<int, char> serializationRule);
		static int** Deserialize(const string str, map<char, int> deserializationRule);
	};
}