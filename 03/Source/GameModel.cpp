#include "CellState.h"
#include "GameModel.h"
#include "SquareMatrix.h"
#include "MatrixSerializator.h"

namespace GameOfLifeModel {
	GameOfLifeModel::GameModel::GameModel(unsigned int fieldSize) {
		_field = SquareMatrix<CellState>(fieldSize);
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
		for (int y = 0; y < getFieldSize(); ++y) {
			for (int x = 0; x < getFieldSize(); ++x) {
				_field.setXY(x, y, CellState::Dead);
			}
		}
	}

	void GameModel::set(int x, int y, CellState cellState) {
		_field.setXY(x, y, cellState);
	}

	void GameModel::step(unsigned int n) {
		int size = _field.getSize();
		bool isEnd = _isEnd;

		for (int i = n; i > 0; --i) {
			if (_isEnd) {
				isEnd = true;
			}
			isEnd = true;
			SquareMatrix<CellState> buf = _field;

			for (int y = 0; y < size; ++y) {
				for (int x = 0; x < size; ++x) {
					int aliveNeighbours = 0;
					aliveNeighbours += _field.getXY((x - 1) % size, (y - 1) % size);
					aliveNeighbours += _field.getXY(x % size, (y - 1) % size);
					aliveNeighbours += _field.getXY((x + 1) % size, (y - 1) % size);

					aliveNeighbours += _field.getXY((x - 1) % size, y % size);
					aliveNeighbours += _field.getXY((x + 1) % size, y % size);

					aliveNeighbours += _field.getXY((x - 1) % size, (y + 1) % size);
					aliveNeighbours += _field.getXY(x % size, (y + 1) % size);
					aliveNeighbours += _field.getXY((x + 1) % size, (y + 1) % size);

					CellState oldState = buf.getXY(x, y);
					CellState newState;
					if (oldState == CellState::Alive) {
						if (aliveNeighbours != 3) {
							newState = Dead;
							isEnd = false;
						}
						else {
							newState = Alive;
						}
					}
					else {
						if ((aliveNeighbours >= 2) && (aliveNeighbours <= 3)) {
							newState = Alive;
							isEnd = false;
						}
						else {
							newState = Dead;
						}
					}

					buf.setXY(x, y, newState);
				}
			}
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
