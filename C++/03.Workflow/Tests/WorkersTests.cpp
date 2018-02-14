#include "gtest.h"
#include "StringHelper.h"

#include "DumpWorker.h"
#include "GrepWorker.h"
#include "ReadfileWorker.h"
#include "ReplaceWorker.h"
#include "SortWorker.h"
#include "WritefileWorker.h"

using namespace Workers;

void testWorker(std::string input, std::string expectedOutput, BaseWorker& worker) {
	std::vector<std::string> output = worker.Execute(Tools::StringHelper::ParseTextToLines(input));
	ASSERT_EQ(expectedOutput, Tools::StringHelper::GenerateTextFromLines(output));
}

TEST(WorkersTests, GetValidArgsNumber) {
	ASSERT_EQ(1, DumpWorker(-1, {}).GetValidArgsNumber());
	ASSERT_EQ(1, GrepWorker(-1, {}).GetValidArgsNumber());
	ASSERT_EQ(1, ReadfileWorker(-1, {}).GetValidArgsNumber());
	ASSERT_EQ(2, ReplaceWorker(-1, {}).GetValidArgsNumber());
	ASSERT_EQ(0, SortWorker(-1, {}).GetValidArgsNumber());
	ASSERT_EQ(1, WritefileWorker(-1, {}).GetValidArgsNumber());
}

TEST(WorkersTests, ReadfileWorkerTests) {
	std::string path = "test.txt";
	std::string fileContent =
		"Read me\n"
		"Pls\n"
		"Meh..";
	Tools::StringHelper::PrintTextToFile(path, fileContent);
	testWorker("Doesn't matter", fileContent, ReadfileWorker(-1, { path }));
}

TEST(WorkersTests, WritefileWorkerTests) {
	std::string path = "test.txt";
	std::string input =
		"Sample text\n"
		"Here!\n"
		"Okay...";
	testWorker(input, input, WritefileWorker(-1, { path }));
	std::string fileContent = Tools::StringHelper::GetTextFromFile(path);
	ASSERT_EQ(input, fileContent);
}

TEST(WorkersTests, GrepWorkerTests) {
	std::string input =
		"absccc\n"
		"efefefekey\n"
		"asassdkke\n"
		"yefe\n"
		"key";
	std::string expectedOutput =
		"efefefekey\n"
		"key";
	testWorker(input, expectedOutput, GrepWorker(-1, { "key" }));
}

TEST(WorkersTests, SortWorkerTests) {
	std::string input =
		"absccc\n"
		"efefefekey\n"
		"asassdkke\n"
		"yefe\n"
		"key";
	std::string expectOutput =
		"absccc\n"
		"asassdkke\n"
		"efefefekey\n"
		"key\n"
		"yefe";
	testWorker(input, expectOutput, SortWorker(-1, {}));
}

TEST(WorkersTests, ReplaceWorkerTests) {
	std::string input =
		"Such a nice cat!\n"
		"Very good cat!\n"
		"Yeah, my Cattson!";
	std::string expectedOutput =
		"Such a nice fluffy dog!\n"
		"Very good fluffy dog!\n"
		"Yeah, my Cattson!";
	testWorker(input, expectedOutput, ReplaceWorker(-1, { "cat", "fluffy dog" }));
}

TEST(WorkersTests, DumpWorkerTests) {
	std::string path = "test.txt";
	std::string input =
		"Sample text\n"
		"Here!\n"
		"Okay...";
	testWorker(input, input, DumpWorker(-1, { path }));
	std::string fileContent = Tools::StringHelper::GetTextFromFile(path);
	ASSERT_EQ(input, fileContent);
}