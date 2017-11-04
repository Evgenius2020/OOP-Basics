#include <string>
#include <vector>
#include "gtest.h"
#include "InputParser.h"

using namespace Building;

TEST(InputParserTests, DefaultInputMetadataValues) {
	InputMetadata inputMetadata;
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);
	ASSERT_EQ(0, inputMetadata.ExecutionOrder.size());
	ASSERT_EQ(0, inputMetadata.NonParsedWorkersMap.size());
}

TEST(InputParserTests, SpecifiedWorkers) {
	std::vector<std::string> args;
	InputMetadata inputMetadata;

	args = { "workflow.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "workflow.txt", "-o" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "workflow.txt", "-o", "-o" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("-o", inputMetadata.SpecifiedOutput);

	args = { "workflow.txt", "-i", "input.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("input.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "workflow.txt", "-o", "output.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output.txt", inputMetadata.SpecifiedOutput);

	args = { "workflow.txt", "-i", "input.txt", "-o", "output.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("input.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output.txt", inputMetadata.SpecifiedOutput);

	args = { "workflow.txt", "-o", "output.txt", "-i", "input.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("input.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output.txt", inputMetadata.SpecifiedOutput);

	args = { "workflow.txt", "-i", "input1.txt", "-i", "input2.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("input2.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "workflow.txt", "-o", "output1.txt", "-o", "output2.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output2.txt", inputMetadata.SpecifiedOutput);

	args = { "workflow.txt", "-o", "output1.txt", "-o", "output2.txt", "-o", "output3.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output2.txt", inputMetadata.SpecifiedOutput);
}