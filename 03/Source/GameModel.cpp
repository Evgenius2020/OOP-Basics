#include <string>
#include "CellState.h"
#include "SquareMatrix.h"
#include "GameModel.h"
#include "MatrixSerializator.h"

namespace GameOfLifeModel {
	GameModel::GameModel() : GameModel(0) {}

	GameModel::GameModel(unsigned int fieldSize) {
		_field = SquareMatrix(fieldSize);
		_isEnd = false;
		_stepNumber = 0;
	}

	unsigned int GameModel::getStepNumber() {
		return _stepNumber;
	}

	unsigned int GameModel::getFieldSize() {
		return _field.getSize();
	}

	bool GameModel::getIsEnd() {
		return _isEnd;
	}

	void GameModel::reset() {
		_isEnd = false;
		for (unsigned int y = 0; y < getFieldSize(); ++y) {
			for (unsigned int x = 0; x < getFieldSize(); ++x) {
				_field.setXY(x, y, CellState::Dead);
			}
		}
	}

	void GameModel::set(int x, int y, CellState cellState) {
		_isEnd = false;
		_field.setXY(x, y, cellState);
	}

	void GameModel::step(unsigned int n) {
		int size = _field.getSize();

		for (int i = n; i > 0; --i) {
			if (_isEnd) {
				return;
			}
			_isEnd = true;
			SquareMatrix buf(_field);

			for (int y = 0; y < size; ++y) {
				for (int x = 0; x < size; ++x) {
					int aliveNeighbours = 0;
					aliveNeighbours += (int)_field.getXY((x - 1 + size) % size, (y - 1 + size) % size);
					aliveNeighbours += (int)_field.getXY(x % size, (y - 1 + size) % size);
					aliveNeighbours += (int)_field.getXY((x + 1) % size, (y - 1 + size) % size);

					aliveNeighbours += (int)_field.getXY((x - 1 + size) % size, y % size);
					aliveNeighbours += (int)_field.getXY((x + 1) % size, y % size);

					aliveNeighbours += (int)_field.getXY((x - 1 + size) % size, (y + 1) % size);
					aliveNeighbours += (int)_field.getXY(x % size, (y + 1) % size);
					aliveNeighbours += (int)_field.getXY((x + 1) % size, (y + 1) % size);

					CellState oldState = buf.getXY(x, y);
					CellState newState = oldState;
					if (oldState == CellState::Dead) {
						if (aliveNeighbours == 3) {
							newState = Alive;
							_isEnd = false;
						}
					}
					else {
						if ((aliveNeighbours < 2) || (aliveNeighbours > 3)) {
							newState = Dead;
							_isEnd = false;
						}
					}

					buf.setXY(x, y, newState);
				}
			}

			_field = buf;
		}
	}

	const std::string GameModel::fieldToStr() {
		return MatrixSerializator::Serialize(_field);
	}

	void GameModel::setFieldFromStr(const std::string str) {
		_field = MatrixSerializator::Deserialize(str);
		_isEnd = false;
	}
}
