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
		unsigned int _stepNumber;
		bool _isEnd;
	public:
		GameModel();
		GameModel(unsigned int fieldSize);

		unsigned int getStepNumber();
		unsigned int getFieldSize();
		bool getIsEnd();

		void reset();
		void set(int x, int y, CellState cellState);
		void step(unsigned int n);
		void back();
		const std::string fieldToStr();
		void setFieldFromStr(const std::string str);
	};
}