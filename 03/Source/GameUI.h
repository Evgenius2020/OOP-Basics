#pragma once
#include <string>
#include "GameModel.h"

namespace GameOfLifeView {
	class GameUI {
	private:
		GameOfLifeModel::GameModel _gameModel;
	public:
		GameUI(unsigned int fieldSize);
		void Run();
	};
}