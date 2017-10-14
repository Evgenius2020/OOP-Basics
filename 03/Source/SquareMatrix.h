#pragma once

template <typename T>
class SquareMatrix {
private:
	T* _data;
	unsigned int _size;
public:
	SquareMatrix(unsigned int size);

	unsigned int getSize;

	T getXY(unsigned int x, unsigned int y);
	void setXY(unsigned int x, unsigned int y, T val);
};