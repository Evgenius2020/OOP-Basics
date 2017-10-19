#include "SquareMatrix.h"
#include "CellState.h"

namespace GameOfLifeModel {
	SquareMatrix::SquareMatrix() {
		_size = 0;
		_data = nullptr;
	}

	SquareMatrix::SquareMatrix(unsigned int size) {
		_size = size;
		_data = new CellState[size*size];
		for (int i = 0; i < size*size; ++i) {
			_data[i] = (CellState)0;
		}
	}

	SquareMatrix::SquareMatrix(const SquareMatrix& another) {
		_size = another._size;
		_data = new CellState[_size * _size];
		for (int i = 0; i < _size * _size; ++i) {
			_data[i] = another._data[i];
		}
	}

	unsigned int SquareMatrix::getSize() {
		return _size;
	}

	SquareMatrix& SquareMatrix::operator=(const SquareMatrix& another) {
		_size = another._size;
		_data = new CellState[_size * _size];
		for (int i = 0; i < _size * _size; ++i) {
			_data[i] = another._data[i];
		}
		return *this;
	}

	CellState SquareMatrix::getXY(unsigned int x, unsigned int y) {
		return _data[y * _size + x];
	}

	void SquareMatrix::setXY(unsigned int x, unsigned int y, CellState val) {
		_data[y * _size + x] = val;
	}
}