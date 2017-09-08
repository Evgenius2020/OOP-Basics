#include "src\gtest-all.cc"
#include "trit_set.h"

using namespace Trit_Set;

//TEST(TritSetTest, BasicTests) {
//	TritSet set(1000);
//	// length of internal array
//	size_t allocLength = set.capacity();
//	ASSERT_GE(allocLength, 1000 * 2 / 8 / sizeof(int));
//
//	//не выделяет никакой памяти
//	set[1000000000] = Trit::Unknown;
//	ASSERT_EQ(allocLength, set.capacity());
//
//	// false, but no exception or memory allocation
//	if (set[2000000000] == Trit::True) {}
//	ASSERT_EQ(allocLength, set.capacity());
//
//	//выделение памяти
//	set[1000000000] = Trit::True;
//	ASSERT_LT(allocLength, set.capacity());
//
//	//no memory operations
//	allocLength = set.capacity();
//	set[1000000000] = Trit::Unknown;
//	set[1000000] = False;
//	ASSERT_EQ(allocLength, set.capacity());
//
//	//освобождение памяти до начального значения или 
//	//до значения необходимого для хранения последнего установленного трита
//	//в данном случае для трита 1000’000
//	set.shrink();
//	ASSERT_GT(allocLength, set.capacity());
//}
//
//TEST(TritSetTest, OperationsTests) {
//	TritSet setA(1000);
//	TritSet setB(2000);
//	setA[0] = Trit::True;
//	setB[0] = Trit::False;
//	TritSet setC = setA & setB;
//	ASSERT_EQ(setC.capacity(), setB.capacity());
//	ASSERT_EQ(setC[0], Trit::False);
//}

TEST(g, g) {
	TritSet set(10);
	ASSERT_EQ(set[0], Trit::Unknown);
	set[0] = Trit::True;
	ASSERT_EQ(set[0], Trit::True);
	set[1] = Trit::False;
	ASSERT_EQ(set[0], Trit::True);
	ASSERT_EQ(set[1], Trit::False);
	set[0] = Trit::Unknown;
	ASSERT_EQ(set[0], Trit::Unknown);
	ASSERT_EQ(set[1], Trit::False);

}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}