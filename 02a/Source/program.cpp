#include "src\gtest-all.cc"
#include "Date.h"

using namespace DateTools;

TEST(DateTests, ConstructorsTests) {
	Date date = Date(2017, Month::Jan, 1);
	ASSERT_EQ(2017, date.getYears());
	ASSERT_EQ(Month::Jan, date.getMonths());
	ASSERT_EQ(1, date.getDays());

	Date dateCopy = Date(date);
	ASSERT_EQ(2017, dateCopy.getYears());
	ASSERT_EQ(Month::Jan, dateCopy.getMonths());
	ASSERT_EQ(1, dateCopy.getDays());


}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}