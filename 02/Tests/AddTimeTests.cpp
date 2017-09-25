#include "gtest.h"
#include "../Source/Date.h"

using namespace DateTools;

TEST(AddTimeTests, AddSeconds) {
	Date date = Date(0, 0, 0);
	ASSERT_EQ(0, date.getSeconds());
	ASSERT_EQ(0, date.getMinutes());
	date = date.addSeconds(5);
	ASSERT_EQ(5, date.getSeconds());
	ASSERT_EQ(0, date.getMinutes());
	date = date.addSeconds(65);
	ASSERT_EQ(10, date.getSeconds());
	ASSERT_EQ(1, date.getMinutes());
	date = date.addSeconds(-12);
	ASSERT_EQ(0, date.getMinutes());
	ASSERT_EQ(58, date.getSeconds());
}

TEST(AddTimeTests, AddMinutes) {
	Date date = Date(0, 0, 0);
	ASSERT_EQ(0, date.getMinutes());
	ASSERT_EQ(0, date.getHours());
	ASSERT_EQ(0, date.getSeconds());
	date = date.addMinutes(240);
	ASSERT_EQ(0, date.getMinutes());
	ASSERT_EQ(4, date.getHours());
	ASSERT_EQ(0, date.getSeconds());
	date = date.addMinutes(-241);
	ASSERT_EQ(23, date.getHours());
	ASSERT_EQ(59, date.getMinutes());
	ASSERT_EQ(0, date.getSeconds());
}

TEST(AddTimeTests, AddHours) {
	Date date = Date(1, Month::Jan, 1);
	date = date.addHours(5);
	ASSERT_EQ(1, date.getDay());
	ASSERT_EQ(5, date.getHours());
	date = date.addHours(20);
	ASSERT_EQ(2, date.getDay());
	ASSERT_EQ(1, date.getHours());
	date = date.addHours(-24);
	ASSERT_EQ(1, date.getDay());
	ASSERT_EQ(1, date.getHours());
}

TEST(AddTimeTests, AddDays) {
	Date date = Date(1, Month::Feb, 1);
	date = date.addDays(30);
	ASSERT_EQ(Month::Mar, date.getMonth());
	ASSERT_EQ(3, date.getDay());
	date = Date(4, Month::Feb, 1);
	date = date.addDays(30);
	ASSERT_EQ(2, date.getDay());
	ASSERT_EQ(Month::Mar, date.getMonth());

	date = Date(1, Month::Jan, 1);
	date = date.addDays(365);
	ASSERT_EQ(2, date.getYear());
	ASSERT_EQ(Month::Jan, date.getMonth());
	ASSERT_EQ(1, date.getDay());
	date = Date(4, Month::Jan, 1);
	date = date.addDays(366);
	ASSERT_EQ(5, date.getYear());
	ASSERT_EQ(Month::Jan, date.getMonth());
	ASSERT_EQ(1, date.getDay());
}

TEST(AddTimeTests, AddMonths) {
	Date date = Date(1, Month::Jan, 1);
	date = date.addMonths(25);
	ASSERT_EQ(3, date.getYear());
	ASSERT_EQ(Month::Feb, date.getMonth());
	ASSERT_EQ(1, date.getDay());
	date = date.addMonths(-26);
	ASSERT_EQ(9999, date.getYear());
	ASSERT_EQ(Month::Dec, date.getMonth());
	ASSERT_EQ(1, date.getDay());
}

TEST(AddTimeTests, AddYears) {
	Date date = Date(5, Month::Jan, 1);
	date = date.addYears(9999);
	ASSERT_EQ(5, date.getYear());
	date = date.addYears(-5);
	ASSERT_EQ(9999, date.getYear());
}

TEST(AddTimeTests, UnmodifyingLogic) {
	Date date = Date(1, Month::Jan, 1, 0, 0, 0);
	ASSERT_EQ(1, date.getYear());
	ASSERT_EQ(Month::Jan, date.getMonth());
	ASSERT_EQ(1, date.getDay());
	ASSERT_EQ(0, date.getHours());
	ASSERT_EQ(0, date.getMinutes());
	ASSERT_EQ(0, date.getSeconds());
	date.addYears(1);
	date.addDays(1);
	date.addMonths(1);
	date.addHours(1);
	date.addMinutes(1);
	date.addSeconds(1);
	ASSERT_EQ(1, date.getYear());
	ASSERT_EQ(Month::Jan, date.getMonth());
	ASSERT_EQ(1, date.getDay());
	ASSERT_EQ(0, date.getHours());
	ASSERT_EQ(0, date.getMinutes());
	ASSERT_EQ(0, date.getSeconds());
	date = date.addYears(1);
	date = date.addDays(1);
	date = date.addMonths(1);
	date = date.addHours(1);
	date = date.addMinutes(1);
	date = date.addSeconds(1);
	ASSERT_EQ(2, date.getYear());
	ASSERT_EQ(Month::Feb, date.getMonth());
	ASSERT_EQ(2, date.getDay());
	ASSERT_EQ(1, date.getHours());
	ASSERT_EQ(1, date.getMinutes());
	ASSERT_EQ(1, date.getSeconds());
}