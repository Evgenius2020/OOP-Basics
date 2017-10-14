#include "GameModel.h"

namespace GameOfLifeModel {
	GameOfLifeModel::GameModel::GameModel(const int fieldSize) {
		_field = new CellState[fieldSize*fieldSize];
	}
}
