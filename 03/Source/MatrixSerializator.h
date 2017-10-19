#include <map>
#include <string>
#include "SquareMatrix.h"
#include "CellState.h"

namespace GameOfLifeModel {
	class MatrixSerializator {
	public:
		static std::string Serialize(SquareMatrix matrix);
		static SquareMatrix Deserialize(const std::string str);
	};
}