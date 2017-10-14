#include <iostream>
#include "GameUI.h"
#include "GameModel.h"
#include "CommandsExecutor.h"

void printHelp() {
	std::cout << "Help here" << std::endl;
}

namespace GameOfLifeView {
	GameUI::GameUI(unsigned int fieldSize) {
		_gameModel = GameOfLifeModel::GameModel(fieldSize);
	}

	void GameUI::Run() {
		while (1) {
			std::string cmd;
			if (_gameModel.getIsEnd()) {
				std::cout << "Game Stoped!" << std::endl;
			}
			std::cout << _gameModel.fieldToStr() << std::endl;
			std::getline(std::cin, cmd);
			
			if (cmd == "exit") {
				return;
			}
			else if (cmd == "help") {
				printHelp();
			}
			else {
				const std::string resStr = GameOfLifeController::CommandsExecutor::Execute(cmd, _gameModel);
				std::cout << resStr << std::endl;
			}
		}
	}
}