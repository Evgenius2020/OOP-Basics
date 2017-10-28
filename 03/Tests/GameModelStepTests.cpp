#include <string>
#include "gtest.h"
#include "GameModel.h"
#include "MatrixSerializator.h"

using namespace GameOfLifeModel;

void runTestCase(std::string in, std::string expect) {
	SquareMatrix inField = MatrixSerializator::Deserialize(in);
	SquareMatrix expectField = MatrixSerializator::Deserialize(expect);
	GameModel model(0);
	model.setField(inField);
	model.step(1);
	SquareMatrix actual = model.getField();
	ASSERT_EQ(expectField, actual);
}

TEST(GameModelStepTests, NohingIfEmptyField) {
	// ...		...
	// ...  ==>	... 	
	// ...		...
	runTestCase("... ... ...", "... ... ...");
}

TEST(GameModelStepTests, KillingCell) {
	// ...		...
	// .*.  ==>	... 	
	// ...		...
	runTestCase("... .*. ...", "... ... ...");
}

TEST(GameModelStepTests, SettlingNeighbourCells) {
	// ....		....
	// .*.. ==> .**.
	// .**.		.**.
	// ....		....
	runTestCase(".... .*.. .**. ....", ".... .**. .**. ....");
}

TEST(GameModelStepTests, Angle) {
	// ..*.		..**
	// ...* ==> ....
	// ....		....
	// ...*		....
	runTestCase("..*. ...* .... ...*", "..** .... .... ....");
}

TEST(GameModelStepTests, Angles) {
	// ..*.		.***
	// .*.* ==> ****
	// *...		****
	// ..*.		.*.*
	runTestCase("..*. .*.* *... ..*.", ".*** **** **** .*.*");
}

TEST(GameModelStepTests, Stick) {
	// .....		.....
	// ..*..		.....
	// ..*..  ==>	.***.	
	// ..*..		.....
	// .....		.....
	runTestCase("..... ..*.. ..*.. ..*.. .....", "..... ..... .***. ..... .....");
}