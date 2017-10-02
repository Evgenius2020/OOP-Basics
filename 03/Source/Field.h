#pragma once
#include <string>
#include "CellState.h"

namespace GameOfLife {
	class Field {
	private:
		CellState field[10][10];
	public:
		void reset();
		void set(int x, int y, CellState state);
		void set(CellState field[10][10]);
		const CellState** get();
		void next();
		void prev();
	};
}