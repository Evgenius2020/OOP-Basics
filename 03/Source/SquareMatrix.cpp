#include "SquareMatrix.h"
#include "CellState.h"

namespace GameOfLifeModel {
	SquareMatrix<CellState>::SquareMatrix() {
		_size = 0;
		_data = nullptr;
	}

	SquareMatrix<CellState>::SquareMatrix(unsigned int size) {
		_size = size;
		_data = new CellState[size*size];
		for (int i = 0; i < size*size; ++i) {
			_data[i] = (CellState)0;
		}
	}

	unsigned int SquareMatrix<CellState>::getSize() {
		return _size;
	}

	CellState SquareMatrix<CellState>::getXY(unsigned int x, unsigned int y) {
		return _data[y * _size + x];
	}

	void SquareMatrix<CellState>::setXY(unsigned int x, unsigned int y, CellState val) {
		_data[y * _size + x] = val;
	}
}