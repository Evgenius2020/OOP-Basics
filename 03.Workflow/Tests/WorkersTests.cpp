#include "gtest.h"
#include "StringHelper.h"
#include "GrepWorker.h"
#include "SortWorker.h"
#include "ReplaceWorker.h"

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

TEST(WorkersTests, ReplaceWorkerTests) {
	std::string input =
		"Such a nice cat!\n"
		"Very good cat!\n"
		"Yeah, my Cattson!";
	std::string exceptOutput = 
		"Such a nice fluffy dog!\n"
		"Very good fluffy dog!\n"
		"Yeah, my Cattson!";
	ReplaceWorker replaceWorker(-1, { "cat", "fluffy dog" });
	std::vector<std::string> output = replaceWorker.Execute(Tools::StringHelper::ParseTextToLines(input));
	ASSERT_EQ(exceptOutput, Tools::StringHelper::GenerateTextFromLines(output));
}