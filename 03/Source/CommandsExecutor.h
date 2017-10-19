#pragma once
#include <string>
#include <map>
#include "GameModel.h"

namespace GameOfLifeController {
	class CommandsExecutor {
	public:
		static const std::string Execute(std::string cmd, GameOfLifeModel::GameModel& gameModel);
	};
}