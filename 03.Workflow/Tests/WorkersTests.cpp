#include "gtest.h"
#include "GrepWorker.h"
#include "StringHelper.h"

using namespace Workers;

TEST(WorkersTests, GrepWorkerTests) {
	std::string input =
		"absccc\n"
		"efefefekey\n"
		"\n"
		"asassdkke\n"
		"yefe\n"
		"key\n";
	std::string exceptOutput =
		"efefefekey\n"
		"key";
	GrepWorker grepWorker(-1, { "key" });
	std::vector<std::string> output = grepWorker.Execute(Tools::StringHelper::ParseTextToLines(input));
	ASSERT_EQ(exceptOutput, Tools::StringHelper::GenerateTextFromLines(output));
}