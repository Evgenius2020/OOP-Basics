#include "gtest.h"
#include "Date.h"

using namespace DateTools;

TEST(ToStingTests, AllFields) {
	Date date(2017, Month::Jan, 1, 22, 22, 33);
	std::string str = date.toString();
	ASSERT_EQ("2017-Jan-1 22::22::33", str);
	date = Date(1, Month::Jul, 30, 1, 1, 1);
	str = date.toString();
	ASSERT_EQ("1-Jul-30 1::1::1", str);
}