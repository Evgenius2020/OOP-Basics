#include "SquareMatrix.h"

namespace GameOfLifeModel {
	template<typename T>
	SquareMatrix<T>::SquareMatrix() : SquareMatrix(0) { }

	template <typename T>
	SquareMatrix<T>::SquareMatrix(unsigned int size) {
		_size = size;
		_data = new T[size*size];
	}

	template<typename T>
	unsigned int SquareMatrix<T>::getSize() {
		return _size;
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