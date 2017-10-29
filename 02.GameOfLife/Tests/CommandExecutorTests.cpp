#include "gtest.h"
#include "CommandsExecutor.h"
#include "GameModel.h"

using namespace GameOfLifeController;
using namespace GameOfLifeModel;

TEST(CommandsExecutorTests, WrongCommandsTests) {
	GameModel model(5);
	std::string result = CommandsExecutor::Execute("set A5", model);
	ASSERT_EQ("Wrong Command", result);
	result = CommandsExecutor::Execute("set A4 ", model);
	ASSERT_EQ("Wrong Command", result);
	result = CommandsExecutor::Execute("set a4", model);
	ASSERT_EQ("Wrong Command", result);
}

TEST(CommandExecutorTests, SetClear) {
	GameModel model(5);
	CommandsExecutor::Execute("set A4", model);
	ASSERT_EQ(CellState::Alive, ((const SquareMatrix)model.getField()).getXY(0, 4));
	CommandsExecutor::Execute("clear A4", model);
	ASSERT_EQ(CellState::Dead, ((const SquareMatrix)model.getField()).getXY(0, 4));
}

TEST(CommandExecutorTests, SaveLoad) {
	GameModel model(5);
	model.step();
	CommandsExecutor::Execute("save out.txt", model);
	ASSERT_TRUE(model.getIsEnd());
	CommandsExecutor::Execute("load out.txt", model);
	ASSERT_FALSE(model.getIsEnd());

	model.set(1, 4, CellState::Alive);
	ASSERT_EQ(CellState::Alive, ((const SquareMatrix)model.getField()).getXY(1, 4));
	CommandsExecutor::Execute("load out.txt", model);
	ASSERT_EQ(CellState::Dead, ((const SquareMatrix)model.getField()).getXY(1, 4));
}

TEST(CommandExecutorTests, StepBackReset) {
	GameModel model(5);
	model.set(1, 4, CellState::Alive);
	model.step();
	ASSERT_EQ(CellState::Dead, ((const SquareMatrix)model.getField()).getXY(1, 4));
	model.step();
	ASSERT_TRUE(model.getIsEnd());
	model.reset();
	ASSERT_FALSE(model.getIsEnd());
	ASSERT_EQ(CellState::Dead, ((const SquareMatrix)model.getField()).getXY(1, 4));
	model.back();
	ASSERT_FALSE(model.getIsEnd());
	ASSERT_EQ(CellState::Dead, ((const SquareMatrix)model.getField()).getXY(1, 4));
	model.back();
	ASSERT_FALSE(model.getIsEnd());
	ASSERT_EQ(CellState::Dead, ((const SquareMatrix)model.getField()).getXY(1, 4));
	model.back();
	ASSERT_FALSE(model.getIsEnd());
	ASSERT_EQ(CellState::Alive, ((const SquareMatrix)model.getField()).getXY(1, 4));
}