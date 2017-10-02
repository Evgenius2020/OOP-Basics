#pragma once
#include "Field.h"
#include "CellState.h"

namespace GameOfLife {
	class GameModel {
	private:
		Field field;
		int stepNumber;
	public:
		bool isEnd();
		int getStepNumber();
		void reset();
		void set(int x, int y, CellState state);
		void step(int n);
		std::string fieldToStr();
		void load(std::string field);
	};
}