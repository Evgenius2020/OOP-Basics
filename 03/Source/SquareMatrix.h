#pragma once
#include "CellState.h"

namespace GameOfLifeModel {
	class SquareMatrix {
	private:
		CellState* _data;
		unsigned int _size;
	public:
		SquareMatrix();
		SquareMatrix(unsigned int size);
		SquareMatrix(const SquareMatrix& another);

		unsigned int getSize();

		SquareMatrix& operator=(const SquareMatrix& another);
		bool operator==(const SquareMatrix another) const;
		bool operator!=(const SquareMatrix another) const;

		CellState getXY(unsigned int x, unsigned int y);
		void setXY(unsigned int x, unsigned int y, CellState val);
	};
}