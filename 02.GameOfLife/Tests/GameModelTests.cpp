#include "gtest.h"
#include "GameModel.h"
#include "MatrixSerializator.h"

using namespace GameOfLifeModel;

TEST(GameModelTests, Constructors) {
	GameModel model = GameModel();
	ASSERT_FALSE(model.getIsEnd());
	ASSERT_EQ(0, model.getFieldSize());
	model = GameModel(5);
	ASSERT_FALSE(model.getIsEnd());
	ASSERT_EQ(5, model.getFieldSize());
}

TEST(GameModelTests, GetSetField) {
	GameModel model(5);
	SquareMatrix field = model.getField();
	ASSERT_EQ(5, field.getSize());
	field.setXY(4, 1, CellState::Alive);
	ASSERT_NE(CellState::Alive, ((const SquareMatrix)model.getField()).getXY(4, 1));
	model = GameModel();
	ASSERT_EQ(0, model.getFieldSize());
	model.setField(field);
	ASSERT_EQ(5, model.getFieldSize());
	ASSERT_EQ(CellState::Alive, ((const SquareMatrix)model.getField()).getXY(4, 1));
}

TEST(GameModelTests, GetSetCell) {
	GameModel model(5);
	model.set(4, 1, CellState::Alive);
	ASSERT_EQ(CellState::Alive, ((const SquareMatrix)model.getField()).getXY(4, 1));
}

TEST(GameModelTests, BackReset) {
	GameModel model(0);
	model.setField(SquareMatrix(5));
	model.set(4, 1, CellState::Alive);
	model.reset();

	ASSERT_EQ(5, model.getFieldSize());
	ASSERT_EQ(CellState::Dead, ((const SquareMatrix)model.getField()).getXY(4, 1));
	model.back();
	ASSERT_EQ(5, model.getFieldSize());
	ASSERT_EQ(CellState::Alive, ((const SquareMatrix)model.getField()).getXY(4, 1));
	model.back();
	ASSERT_EQ(5, model.getFieldSize());
	ASSERT_EQ(CellState::Dead, ((const SquareMatrix)model.getField()).getXY(4, 1));
	model.back();
	ASSERT_EQ(0, model.getFieldSize());
}