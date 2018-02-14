#include "gtest.h"
#include "StringHelper.h"

using namespace Tools;

TEST(StringHelperTests, ParseTextToLines) {
	std::string input =
		"absccc\n"
		"efefefekey\n"
		"\na\n\n"
		"asassdkke\n"
		"yefe\n"
		"key\n";
	std::vector<std::string> expectedOutput({ "absccc", "efefefekey", "", "a", "", "asassdkke", "yefe", "key" });
	ASSERT_EQ(expectedOutput, StringHelper::ParseTextToLines(input));
}

TEST(StringHelperTests, GenerateTextFromLines) {
	std::string endl = StringHelper::GetEndl();
	std::vector<std::string> input({ "absccc", "efefefekey", "a", "asassdkke", "yefe", "key" });
	std::string expectedOutput = "absccc" + endl + "efefefekey" + endl + "a" + endl + "asassdkke" + endl + "yefe" + endl + "key";
	ASSERT_EQ(expectedOutput, StringHelper::GenerateTextFromLines(input));
}

TEST(StringHelperTests, IntToStr) {
	ASSERT_EQ("5", StringHelper::IntToStr(5));
	ASSERT_EQ("-5", StringHelper::IntToStr(-5));
}