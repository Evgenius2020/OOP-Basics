#include "SquareMatrix.h"

namespace GameOfLifeModel {
	template <typename T>
	SquareMatrix<T>::SquareMatrix(unsigned int size) {
		_size = size;
		_data = new int[size*size];
	}

	template<typename T>
	T SquareMatrix<T>::getXY(unsigned int x, unsigned int y) {
		return _data[y * _size + x];
	}

	template<typename T>
	void SquareMatrix<T>::setXY(unsigned int x, unsigned int y, T val) {
		_data[y * _size + x] = val;
	}
}