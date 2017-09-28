#include "gtest.h"
#include "Date.h"
#include "DateInterval.h"
#include "Month.h"

using namespace DateTools;

TEST(AddIntervalTests, WithoutNormalization) {
	Date date(1, Jan, 1, 1, 1, 1);
	DateInterval interval(1, 1, 1, 1, 1, 1);
	date = date.addInterval(interval);
	ASSERT_EQ(2, date.getYear());
	ASSERT_EQ(Feb, date.getMonth());
	ASSERT_EQ(2, date.getDay());
	ASSERT_EQ(2, date.getHours());
	ASSERT_EQ(2, date.getMinutes());
	ASSERT_EQ(2, date.getSeconds());

	date = date.addInterval(DateInterval(-1, -1, -1, -1, -1, -1));
	ASSERT_EQ(1, date.getYear());
	ASSERT_EQ(Jan, date.getMonth());
	ASSERT_EQ(1, date.getDay());
	ASSERT_EQ(1, date.getHours());
	ASSERT_EQ(1, date.getMinutes());
	ASSERT_EQ(1, date.getSeconds());
}

TEST(AddIntervalTests, WithNormalization) {
	Date date(1, Mar, 1, 0, 0, 0);
	date = date.addInterval(DateInterval(0, 0, 0, 0, 0, -1));
	ASSERT_EQ(1, date.getYear());
	ASSERT_EQ(Feb, date.getMonth());
	ASSERT_EQ(28, date.getDay());
	ASSERT_EQ(23, date.getHours());
	ASSERT_EQ(59, date.getMinutes());
	ASSERT_EQ(59, date.getSeconds());
}