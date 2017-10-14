#pragma once
#include "CellState.h"
#include <string>
#include <map>

namespace GameOfLife {
	class GameModel {
	private:
		CellState** _field;
		int _stepNumber;
		int _fieldSize;
		int _isEnd;
	public:
		GameModel(int fieldSize);

		int getStepNumber();
		int getFieldSize();
		bool getIsEnd();
		
		void reset();
		void set(int x, int y, CellState state);
		void step(unsigned int n);
		void back();
		const std::string fieldToStr();
		void setFieldFromStr(const std::string str);
	};
}