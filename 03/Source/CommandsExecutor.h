#pragma once
#include <string>
#include <map>
#include "GameModel.h"

namespace GameOfLifeController {
	static class CommandsExecutor {
	public:
		static bool checkValid(std::string cmd);
		static const std::string execute(std::string cmd, GameOfLifeModel::GameModel gameModel);
	};
}

static const std::map<std::string, int> ConsoleInterface = { { "reset", 0 },{ "set", 2 },{ "clear", 2 },{ "back", 0 } ,{ "save", 1 },{ "load", 1 } };
