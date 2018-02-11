#include "gtest.h"
#include "SquareMatrix.h"

using namespace GameOfLifeModel;

TEST(SquareMatrixTests, ConstructorDefautValues) {
	SquareMatrix matrix(5);
	for (unsigned int y = 0; y < 5; y++) {
		for (unsigned int x = 0; x < 5; x++) {
			ASSERT_EQ(CellState::Dead, matrix.getXY(x, y));
		}
	}
}

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

TEST(SquareMatrixTests, AssignOperator) {
	SquareMatrix matrix1(3);
	SquareMatrix matrix2(5);
	ASSERT_NE(matrix1.getSize(), matrix2.getSize());
	matrix2.setXY(4, 4, CellState::Alive);
}

TEST(SquareMatrixTests, EqualOperator) {
	SquareMatrix matrix1(3);
	SquareMatrix matrix2(3);
	ASSERT_TRUE(matrix1 == matrix2);
	ASSERT_EQ(matrix1, matrix2);
	matrix1.setXY(0, 0, CellState::Alive);
	ASSERT_FALSE(matrix1 == matrix2);
	ASSERT_NE(matrix1, matrix2);
	SquareMatrix matrix3(0);
	ASSERT_NE(matrix1, matrix2);
}