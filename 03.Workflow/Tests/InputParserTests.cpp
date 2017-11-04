#include <string>
#include <vector>
#include "gtest.h"
#include "InputParser.h"

using namespace Building;

TEST(InputParserTests, SpecifiedInputWorker) {
	std::vector<std::string> args = { "workflow.txt" };
	InputMetadata inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.AdditionalInput);
	ASSERT_EQ("", inputMetadata.AdditionalOutput);
}