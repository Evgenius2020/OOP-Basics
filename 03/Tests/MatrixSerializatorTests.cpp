#include "gtest.h"
#include "SquareMatrix.h"
#include "MatrixSerializator.h"

using namespace GameOfLifeModel;

TEST(MatrisSerializatorTests, SaveLoad) {
	SquareMatrix matrix(5);
	matrix.setXY(4, 1, CellState::Alive);
	MatrixSerializator::SerializeToFile(matrix, "buf");
	matrix = MatrixSerializator::DeserializeFromFile("buf");
	ASSERT_EQ(5, matrix.getSize());
	ASSERT_EQ(CellState::Alive, matrix.getXY(4, 1));
}