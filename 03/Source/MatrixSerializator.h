#include <map>
#include <string>
#include "SquareMatrix.h"
#include "CellState.h"

namespace GameOfLifeModel {
	class MatrixSerializator {
	public:
		static std::string Serialize(SquareMatrix<CellState> matrix);
		static SquareMatrix<CellState> Deserialize(const std::string str);
	};
}