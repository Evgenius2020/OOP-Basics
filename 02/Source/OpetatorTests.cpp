#include "gtest.h"
#include "Date.h"

using namespace DateTools;

TEST(OperatorTests, CopiesArray) {
	Date date1 = Date(1, Jan, 4);
	Date date2 = date1;
	date2 = date2.addDays(1);
	ASSERT_NE(date1.getDay(), date2.getDay());
}