#include "GameUI.h"
#include "gtest.cpp"
#include <iostream>
int main(int argc, char* argv[]) {
#ifdef TESTING
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
#else
	GameOfLifeView::GameUI gameUI(10);
	gameUI.Run();
	return 0;
#endif
}