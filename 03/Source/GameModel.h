#pragma once
#include <string>
#include <map>
#include "CellState.h"
#include"Matrix.h"

namespace GameOfLifeModel {
	class GameModel {
	private:
		Matrix _field;
		int _stepNumber;
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