#pragma once
#include <string>
#include "GameModel.h"

namespace GameOfLife {
	class GameUI {
	private:
		GameModel gameModel;
	public:
		void Init();
		bool isEnd();
		GameModel getGameModel();
		std::string toStr();
		std::string executeStr(std::string str);
	};
}