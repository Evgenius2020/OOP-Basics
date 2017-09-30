#include "gtest.h"
#include "Date.h"
#include "DateInterval.h"

using namespace DateTools;

TEST(GetIntervalTests, SimpleCases) {
	Date date1 = Date(1, Jan, 1, 0, 0, 0);
	Date date2 = date1;
	DateInterval interval = date1.getInterval(date2);
	ASSERT_EQ(0, interval.getYears());
	ASSERT_EQ(0, interval.getMonths());
	ASSERT_EQ(0, interval.getDays());
	ASSERT_EQ(0, interval.getHours());
	ASSERT_EQ(0, interval.getMinutes());
	ASSERT_EQ(0, interval.getSeconds());

	date2 = date2.addYears(-1);
	interval = date1.getInterval(date2);
	ASSERT_EQ(9998, interval.getYears());
	ASSERT_EQ(0, interval.getMonths());
	ASSERT_EQ(0, interval.getDays());
	ASSERT_EQ(0, interval.getHours());
	ASSERT_EQ(0, interval.getMinutes());
	ASSERT_EQ(0, interval.getSeconds());

	interval = date2.getInterval(date1);
	ASSERT_EQ(-9998, interval.getYears());
	ASSERT_EQ(0, interval.getMonths());
	ASSERT_EQ(0, interval.getDays());
	ASSERT_EQ(0, interval.getHours());
	ASSERT_EQ(0, interval.getMinutes());
	ASSERT_EQ(0, interval.getSeconds());
}