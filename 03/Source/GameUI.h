#pragma once
#include <string>
#include "GameModel.h"

namespace GameOfLifeView {
	class GameUI {
	private:
		GameOfLifeModel::GameModel _gameModel;
	public:
		GameUI(int fieldSize);
		void Run();
	};
}