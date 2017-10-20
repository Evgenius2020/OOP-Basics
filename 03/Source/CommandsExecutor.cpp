#include <string>
#include "CommandsExecutor.h"

static const std::map<std::string, int> ConsoleInterface = { { "reset", 0 },{ "set", 1 },{ "clear", 1 }, { "step", 1}, { "back", 0 } ,{ "save", 1 },{ "load", 1 } };

namespace GameOfLifeController {
	const std::string CommandsExecutor::Execute(std::string cmd, GameOfLifeModel::GameModel& gameModel) {
		if (cmd.substr(0, 5) == "reset") {
			gameModel.reset();
			return "Succesfully Reseted!";
		}
		else if (cmd.substr(0, 4) == "step") {
			int steps = atoi(cmd.substr(5).data());
			gameModel.step(steps);
			return "Success!";
		}
		else if ((cmd.substr(0, 3) == "set") && (cmd.length() == 6)) {
			int x = cmd[4] - 'A';
			int y = cmd[5] - '0';
			if ((x >= 0) && (x < gameModel.getFieldSize())
				&& (y >= 0) && (y < gameModel.getFieldSize())) {
				gameModel.set(x, y, GameOfLifeModel::CellState::Alive);
				return "Success!";
			}
		}
		else if ((cmd.substr(0, 5) == "clear") && (cmd.length() == 8)) {
			int x = cmd[6] - 'A';
			int y = cmd[7] - '0';
			if ((x < 0) && (x >= gameModel.getFieldSize())
				&& (y < 0) && (y >= gameModel.getFieldSize())) {
				gameModel.set(x, y, GameOfLifeModel::CellState::Dead);
				return "Success!";
			}
		}
		else if (cmd.substr(0, 4) == "back") {
			gameModel.back();
			return "Success!";
		}

		return "Wrong Command";
	}
}
