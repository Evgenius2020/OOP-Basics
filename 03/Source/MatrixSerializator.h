#include <map>
#include <string>
#include "SquareMatrix.h"
#include "CellState.h"

namespace GameOfLifeModel {
	static class MatrixSerializator {
		static std::string Serialize(SquareMatrix<CellState> matrix, const std::map<CellState, char> serializationRule);
		static SquareMatrix<CellState> Deserialize(const std::string str, const std::map<char, CellState> deserializationRule);
	};
}