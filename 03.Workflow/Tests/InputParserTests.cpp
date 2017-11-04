#include <string>
#include <vector>
#include "gtest.h"
#include "InputParser.h"

using namespace Building;

TEST(InputParserTests, DefaultInputMetadataValues) {
	InputMetadata inputMetadata;
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);
	ASSERT_EQ(0, inputMetadata.WorkflowSequence.size());
	ASSERT_EQ(0, inputMetadata.NonParsedWorkersMap.size());
}

TEST(InputParserTests, SpecifiedWorkers) {
	std::vector<std::string> args;
	InputMetadata inputMetadata;

	args = { "" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "", "-o" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "", "-o", "-o" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("-o", inputMetadata.SpecifiedOutput);

	args = { "", "-i", "input.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("input.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "", "-o", "output.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output.txt", inputMetadata.SpecifiedOutput);

	args = { "", "-i", "input.txt", "-o", "output.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("input.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output.txt", inputMetadata.SpecifiedOutput);

	args = { "", "-o", "output.txt", "-i", "input.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("input.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output.txt", inputMetadata.SpecifiedOutput);

	args = { "", "-i", "input1.txt", "-i", "input2.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("input2.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "", "-o", "output1.txt", "-o", "output2.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output2.txt", inputMetadata.SpecifiedOutput);

	args = { "", "-o", "output1.txt", "-o", "output2.txt", "-o", "output3.txt" };
	inputMetadata = InputParser::Parse(args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output2.txt", inputMetadata.SpecifiedOutput);
}

TEST(InputParserTests, NormalWorkflow) {
	std::vector<std::string> args;
	InputMetadata inputMetadata;
	std::string rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed\n"
		"3 -> 2 -> 2 -> 1 -> 3 -> 2";
	args = { rawWorkflowFile };

	bool throwsException = false;
	try {
		inputMetadata = InputParser::Parse(args);
	}
	catch (std::string e) {
		throwsException = true;
	}
	ASSERT_FALSE(throwsException);

	std::vector<std::string> rightVector;
	ASSERT_EQ(3, inputMetadata.NonParsedWorkersMap.size());
	rightVector = { "worker1" };
	ASSERT_EQ(rightVector, inputMetadata.NonParsedWorkersMap[1]);
	rightVector = { "worker2", "arg2_1", "arg2_2" };
	ASSERT_EQ(rightVector, inputMetadata.NonParsedWorkersMap[2]);
	rightVector = { "worker3", "arg3_1" };
	ASSERT_EQ(rightVector, inputMetadata.NonParsedWorkersMap[3]);
	std::vector<int> rightSequence = { 3, 2, 2, 1, 3, 2 };
	ASSERT_EQ(rightSequence, inputMetadata.WorkflowSequence);
}