#include "src\gtest-all.cc"
#include "Date.h"

using namespace DateTools;

TEST(DateTests, ConstructorsTests) {
	Date date = Date(2017, Month::Jan, 1);
	ASSERT_EQ(2017, date.getYear());
	ASSERT_EQ(Month::Jan, date.getMonth());
	ASSERT_EQ(1, date.getDay());

	Date dateCopy = Date(date);
	ASSERT_EQ(2017, dateCopy.getYear());
	ASSERT_EQ(Month::Jan, dateCopy.getMonth());
	ASSERT_EQ(1, dateCopy.getDay());
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}