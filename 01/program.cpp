#include "src/gtest-all.cc"

TEST(SquareRootTest, ZeroAndNegativeNos) {
	ASSERT_EQ(0, 5 -5);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}