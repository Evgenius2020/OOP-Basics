#include <string>
#include <vector>
#include "gtest.h"
#include "InputParser.h"
#include "BuildingExceptions.h"

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

void testForException(std::string rawWorkflowFile, std::string expectExcepsion) {
	std::vector<std::string> args = { rawWorkflowFile };
	InputMetadata inputMetadata;
	std::string exception = NoException;

	try {
		inputMetadata = InputParser::Parse(args);
	}
	catch (std::string e) {
		exception = e;
	}

	ASSERT_EQ(expectExcepsion, exception);
}

TEST(InputParserTests, PasringWorkflowFile) {
	std::string rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed\n"
		"3 -> 2 -> 2 -> 1 -> 3 -> 2";
	testForException(rawWorkflowFile, NoException);
	InputMetadata inputMetadata = InputParser::Parse({ rawWorkflowFile });

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

TEST(InputParserTests, PasringWorkflowFileWithoutSequence) {
	std::string rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowFile, NoException);
	InputMetadata inputMetadata = InputParser::Parse({ rawWorkflowFile });

	std::vector<std::string> rightVector;
	ASSERT_EQ(3, inputMetadata.NonParsedWorkersMap.size());
	rightVector = { "worker1" };
	ASSERT_EQ(rightVector, inputMetadata.NonParsedWorkersMap[1]);
	rightVector = { "worker2", "arg2_1", "arg2_2" };
	ASSERT_EQ(rightVector, inputMetadata.NonParsedWorkersMap[2]);
	rightVector = { "worker3", "arg3_1" };
	ASSERT_EQ(rightVector, inputMetadata.NonParsedWorkersMap[3]);
	ASSERT_EQ(0, inputMetadata.WorkflowSequence.size());
}

TEST(InputParserTests, NormalWorkflowFile) {
	std::string rawWorkflowFile;
	rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowFile, NoException);
}

TEST(InputParserTests, DuplicatedBeginLabelException) {
	std::string rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"desc\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowFile, DuplicatedBeginLabelException);
}

TEST(InputParserTests, DuplicatedEndLabelException) {
	std::string rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed\n"
		"csed";
	testForException(rawWorkflowFile, DuplicatedEndLabelException);
}

TEST(InputParserTests, DuplicatedIdsException) {
	std::string rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"1 = worker1 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowFile, DuplicatedIdsException);
}

TEST(InputParserTests, BeginWithoutEndException) {
	std::string rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1";
	testForException(rawWorkflowFile, BeginWithoutEndException);
}

TEST(InputParserTests, WrongWorkflowSequenceException) {
	std::string rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed\n"
		"2 -> 3 ->3";
	testForException(rawWorkflowFile, WrongWorkflowSequenceException);
}

TEST(InputParserTests, NoAssingingSymbolException) {
	std::string rawWorkflowFile;
	rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"2 =worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowFile, NoAssingingSymbolException + ": 2 =worker2 arg2_1 arg2_2");
	rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"2=worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowFile, NoAssingingSymbolException + ": 2=worker2 arg2_1 arg2_2");
}

TEST(InputParserTests, UnresolvableLineException) {
	std::string rawWorkflowFile;
	rawWorkflowFile =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed\n"; // empty line after 'csed'
	testForException(rawWorkflowFile, UnresolvableLineException + ": ");
	rawWorkflowFile =
		"desc\n"
		"1 worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowFile, UnresolvableLineException + ": 1 worker1");
}

TEST(InputParserTests, WorkersWithoutBeginLabel) {
	std::string rawWorkflowFile;
	rawWorkflowFile =
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowFile, WorkersWithoutBeginLabel);
}

TEST(InputParserTests, BeginLabelWithoutWorkers) {
	std::string rawWorkflowFile;
	rawWorkflowFile =
		"desc\n"
		"csed";
	testForException(rawWorkflowFile, BeginLabelWithoutWorkers);
}

TEST(InputParserTests, SequenceWithoutWorkers) {
	std::string rawWorkflowFile =
		"3 -> 2 -> 2 -> 1 -> 3 -> 2";
	testForException(rawWorkflowFile, SequenceWithoutWorkers);
}