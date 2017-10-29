#include <string>
#include "CommandsExecutor.h"
#include "MatrixSerializator.h"

// ConsoleInterface = { { "reset", 0 },{ "set", 1 },{ "clear", 1 }, { "step", 1}, { "back", 0 } ,{ "save", 1 },{ "load", 1 } };

namespace GameOfLifeController {
	const std::string CommandsExecutor::Execute(std::string cmd, GameOfLifeModel::GameModel& gameModel) {
		if ((cmd.length() == 5) && (cmd.substr(0, 5) == "reset")) {
			gameModel.reset();
			return "Success!";
		}
		else if ((cmd.length() >= 6) && (cmd.substr(0, 4) == "step")) {
			int steps = atoi(cmd.substr(5).data());
			for (int i = 0; i < steps; ++i) {
				gameModel.step();
			}
			return "Success!";
		}
		else if ((cmd.length() == 6) && (cmd.substr(0, 3) == "set")) {
			int x = cmd[4] - 'A';
			int y = cmd[5] - '0';
			if ((x >= 0) && (x < gameModel.getFieldSize())
				&& (y >= 0) && (y < gameModel.getFieldSize())) {
				gameModel.set(x, y, GameOfLifeModel::CellState::Alive);
				return "Success!";
			}
		}
		else if ((cmd.length() == 8) && (cmd.substr(0, 5) == "clear")) {
			int x = cmd[6] - 'A';
			int y = cmd[7] - '0';
			if ((x >= 0) && (x < gameModel.getFieldSize())
				&& (y >= 0) && (y < gameModel.getFieldSize())) {
				gameModel.set(x, y, GameOfLifeModel::CellState::Dead);
				return "Success!";
			}
		}
		else if (cmd == "back") {
			gameModel.back();
			return "Success!";
		}
		else if ((cmd.length() >= 6) && (cmd.substr(0, 4) == "save")) {
			std::string path = cmd.substr(5);
			GameOfLifeModel::MatrixSerializator::SerializeToFile(gameModel.getField(), path);
			return "Success!";
		}
		else if ((cmd.length() >= 6) && (cmd.substr(0, 4) == "load")) {
			std::string path = cmd.substr(5);
			gameModel.setField(GameOfLifeModel::MatrixSerializator::DeserializeFromFile(path));
			return "Success!";
		}

		return "Wrong Command";
	}
}