#include "gtest.h"
#include "StringHelper.h"
#include "GrepWorker.h"
#include "SortWorker.h"

using namespace Workers;

TEST(WorkersTests, GrepWorkerTests) {
	std::string input =
		"absccc\n"
		"efefefekey\n"
		"asassdkke\n"
		"yefe\n"
		"key";
	std::string exceptOutput =
		"efefefekey\n"
		"key";
	GrepWorker grepWorker(-1, { "key" });
	std::vector<std::string> output = grepWorker.Execute(Tools::StringHelper::ParseTextToLines(input));
	ASSERT_EQ(exceptOutput, Tools::StringHelper::GenerateTextFromLines(output));
}

TEST(WorkersTests, SortWorkerTests) {
	std::string input =
		"absccc\n"
		"efefefekey\n"
		"asassdkke\n"
		"yefe\n"
		"key";
	std::string exceptOutput =
		"absccc\n"
		"asassdkke\n"
		"efefefekey\n"
		"key\n"
		"yefe";
	SortWorker sortWorker(-1, {});
	std::vector<std::string> output = sortWorker.Execute(Tools::StringHelper::ParseTextToLines(input));
	ASSERT_EQ(exceptOutput, Tools::StringHelper::GenerateTextFromLines(output));
}