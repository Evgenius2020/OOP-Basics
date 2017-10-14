#include "GameUI.h"
#include "GameModel.h"

namespace GameOfLifeView {
	GameUI::GameUI(int fieldSize) {
		_gameModel = GameOfLifeModel::GameModel(fieldSize);
	}
}
