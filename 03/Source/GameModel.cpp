#include <string>
#include "CellState.h"
#include "SquareMatrix.h"
#include "GameModel.h"
#include "MatrixSerializator.h"

namespace GameOfLifeModel {
	GameModel::GameModel(unsigned int fieldSize) {
		_field = SquareMatrix(fieldSize);
		_isEnd = false;
		_history = std::vector<SquareMatrix>();
	}

	GameModel::GameModel() : GameModel(0) {};

	const SquareMatrix GameModel::getField() {
		return _field;
	}

	void GameModel::setField(SquareMatrix field) {
		_isEnd = false;
		_history.push_back(SquareMatrix(_field));
		_field = field;
	}

	unsigned int GameModel::getFieldSize() {
		return _field.getSize();
	}

	bool GameModel::getIsEnd() {
		return _isEnd;
	}

	void GameModel::reset() {
		setField(SquareMatrix(getFieldSize()));
	}

	void GameModel::set(int x, int y, CellState cellState) {
		_history.push_back(SquareMatrix(_field));
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

			_history.push_back(SquareMatrix(_field));
			_field = buf;
		}
	}

	void GameModel::back() {
		if (_history.size()) {
			_field = _history.back();
			_history.pop_back();
		}
	}
}