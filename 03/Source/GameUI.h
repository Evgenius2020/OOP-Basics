#pragma once
#include <string>
#include "GameModel.h"

namespace GameOfLife {
	class GameUI {
	private:
		GameModel _gameModel;
	public:
		GameUI(int fieldSize);
		void Run();
		std::string executeStr(std::string str);
	};
}