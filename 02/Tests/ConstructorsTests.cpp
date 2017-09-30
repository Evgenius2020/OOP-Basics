#include "gtest.h"
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

TEST(ConstructorsTests, WrongInitializing) {
	Date date = Date(2010, Month::Feb, 30, 22, 59, 72);
	ASSERT_EQ(2010, date.getYear());
	ASSERT_EQ(Month::Mar, date.getMonth());
	ASSERT_EQ(2, date.getDay());
	ASSERT_EQ(23, date.getHours());
	ASSERT_EQ(0, date.getMinutes());
	ASSERT_EQ(12, date.getSeconds());
}