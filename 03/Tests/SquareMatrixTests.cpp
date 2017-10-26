#include "gtest.h"
#include "SquareMatrix.h"

using namespace GameOfLifeModel;

TEST(SquareMatrixTests, ConstructorsTestsGetSize) {
	SquareMatrix matrix = SquareMatrix();
	ASSERT_EQ(0, matrix.getSize());
	matrix = SquareMatrix(3);
	ASSERT_EQ(3, matrix.getSize());
	SquareMatrix matrixCopy(matrix);
	ASSERT_EQ(3, matrixCopy.getSize());
}

TEST(SquareMatrixTests, GetSet) {
	SquareMatrix matrix(5);
	ASSERT_EQ(CellState::Dead, matrix.getXY(4, 1));
	matrix.setXY(4, 1, CellState::Alive);
	ASSERT_EQ(CellState::Alive, matrix.getXY(4, 1));
}

TEST(SquareMatrixTests, CopyConstructorGetSet) {
	SquareMatrix matrix(5);
	SquareMatrix matrixCopy(matrix);
	ASSERT_EQ(matrix.getXY(1, 4), matrixCopy.getXY(1, 4));
	matrixCopy.setXY(1, 4, CellState::Alive);
	ASSERT_NE(matrix.getXY(1, 4), matrixCopy.getXY(1, 4));
}

TEST(SquareMatrixTests, AssignOperatorTests) {
	SquareMatrix matrix1(3);
	SquareMatrix matrix2(5);
	ASSERT_NE(matrix1.getSize(), matrix2.getSize());
	matrix2.setXY(4, 4, CellState::Alive);
}