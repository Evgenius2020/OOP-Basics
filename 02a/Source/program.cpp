#include "src\gtest-all.cc"
#include "Date.h"

using namespace DateTools;

TEST(ConstructorsTests, CopyConstructors) {
	Date date = Date(2017, Month::Jan, 1, 0, 0, 0);
	ASSERT_EQ(2017, date.getYear());
	ASSERT_EQ(Month::Jan, date.getMonth());
	ASSERT_EQ(1, date.getDay());

	Date dateSame = Date(2017, Month::Jan, 1);
	ASSERT_EQ(date.getYear(), dateSame.getYear());
	ASSERT_EQ(date.getMonth(), dateSame.getMonth());
	ASSERT_EQ(date.getDay(), dateSame.getDay());
	ASSERT_EQ(date.getHours(), dateSame.getHours());
	ASSERT_EQ(date.getMinutes(), dateSame.getMinutes());
	ASSERT_EQ(date.getSeconds(), dateSame.getSeconds());

	dateSame = Date(date);
	ASSERT_EQ(date.getYear(), dateSame.getYear());
	ASSERT_EQ(date.getMonth(), dateSame.getMonth());
	ASSERT_EQ(date.getDay(), dateSame.getDay());
	ASSERT_EQ(date.getHours(), dateSame.getHours());
	ASSERT_EQ(date.getMinutes(), dateSame.getMinutes());
	ASSERT_EQ(date.getSeconds(), dateSame.getSeconds());
}

TEST(ConstructorsTests, CurrentTimeConstructors) {
	Date date = Date();

	time_t rawtime;
	time(&rawtime);
	struct tm ptm;
	gmtime_s(&ptm, &rawtime);

	ASSERT_EQ(ptm.tm_year + 1900, date.getYear());
	ASSERT_EQ((Month)(ptm.tm_mon + 1), date.getMonth());
	ASSERT_EQ(ptm.tm_mday, date.getDay());
	ASSERT_EQ(ptm.tm_hour, date.getHours());
	ASSERT_EQ(ptm.tm_min, date.getMinutes());
	ASSERT_GE(ptm.tm_sec, date.getSeconds());

	date = Date(ptm.tm_hour, ptm.tm_min, ptm.tm_sec);
	ASSERT_EQ(ptm.tm_year + 1900, date.getYear());
	ASSERT_EQ((Month)(ptm.tm_mon + 1), date.getMonth());
	ASSERT_EQ(ptm.tm_mday, date.getDay());
	ASSERT_EQ(ptm.tm_hour, date.getHours());
	ASSERT_EQ(ptm.tm_min, date.getMinutes());
	ASSERT_EQ(ptm.tm_sec, date.getSeconds());
}

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
	date.addMinutes(240);
	ASSERT_EQ(0, date.getMinutes());
	ASSERT_EQ(4, date.getHours());
	ASSERT_EQ(0, date.getSeconds());
	date.addMinutes(-241);
	ASSERT_EQ(23, date.getHours());
	ASSERT_EQ(59, date.getMinutes());
	ASSERT_EQ(0, date.getSeconds());
}

TEST(AddTimeTests, AddHours) {
	Date date = Date(1, Month::Jan, 1);
	date.addHours(5);
	ASSERT_EQ(1, date.getDay());
	ASSERT_EQ(5, date.getHours());
	date = date.addHours(20);
	ASSERT_EQ(2, date.getDay());
	ASSERT_EQ(1, date.getHours());
	date.addHours(-24);
	ASSERT_EQ(1, date.getDay());
	ASSERT_EQ(1, date.getHours());
}

TEST(AddTimetests, AddDays) {
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
	ASSERT_EQ(2, date.getYear());
	ASSERT_EQ(Month::Jan, date.getMonth());
	ASSERT_EQ(1, date.getDay());
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}