#include <map>
#include <string>
#include "SquareMatrix.h"
#include "CellState.h"

namespace GameOfLifeModel {
	class MatrixSerializator {
	public:
		static std::string Serialize(SquareMatrix matrix);
		static SquareMatrix Deserialize(const std::string str);
		static bool SerializeToFile(SquareMatrix matrix, const std::string path);
		static SquareMatrix DeserializeFromFile(const std::string path);
	};
}