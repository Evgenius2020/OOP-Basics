#pragma once
#include <string>
#include <map>
#include <vector>
#include "CellState.h"
#include "SquareMatrix.h"

namespace GameOfLifeModel {
	class GameModel {
	private:
		SquareMatrix _field;
		std::vector<SquareMatrix> _history;
		bool _isEnd;
	public:
		GameModel();
		GameModel(unsigned int fieldSize);

		const SquareMatrix getField();
		void SetField(SquareMatrix field);
		unsigned int getFieldSize();
		bool getIsEnd();

		void reset();
		void set(int x, int y, CellState cellState);
		void step(unsigned int n);
		void back();
	};
}