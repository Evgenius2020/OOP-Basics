#include <string>
#include <vector>
#include "gtest.h"
#include "InputParser.h"
#include "Exceptions.h"

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

	args = {};
	inputMetadata = InputParser::Parse("", args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "-o" };
	inputMetadata = InputParser::Parse("", args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "-o", "-o" };
	inputMetadata = InputParser::Parse("", args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("-o", inputMetadata.SpecifiedOutput);

	args = { "-i", "input.txt" };
	inputMetadata = InputParser::Parse("", args);
	ASSERT_EQ("input.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "-o", "output.txt" };
	inputMetadata = InputParser::Parse("", args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output.txt", inputMetadata.SpecifiedOutput);

	args = { "-i", "input.txt", "-o", "output.txt" };
	inputMetadata = InputParser::Parse("", args);
	ASSERT_EQ("input.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output.txt", inputMetadata.SpecifiedOutput);

	args = { "-o", "output.txt", "-i", "input.txt" };
	inputMetadata = InputParser::Parse("", args);
	ASSERT_EQ("input.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output.txt", inputMetadata.SpecifiedOutput);

	args = { "-i", "input1.txt", "-i", "input2.txt" };
	inputMetadata = InputParser::Parse("", args);
	ASSERT_EQ("input2.txt", inputMetadata.SpecifiedInput);
	ASSERT_EQ("", inputMetadata.SpecifiedOutput);

	args = { "-o", "output1.txt", "-o", "output2.txt" };
	inputMetadata = InputParser::Parse("", args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output2.txt", inputMetadata.SpecifiedOutput);

	args = { "-o", "output1.txt", "-o", "output2.txt", "-o", "output3.txt" };
	inputMetadata = InputParser::Parse("", args);
	ASSERT_EQ("", inputMetadata.SpecifiedInput);
	ASSERT_EQ("output2.txt", inputMetadata.SpecifiedOutput);
}

void testForException(std::string rawWorkflowText, std::vector<std::string> args, std::string expectException) {
	InputMetadata inputMetadata;
	std::string exception = NoException;

	try {
		inputMetadata = InputParser::Parse(rawWorkflowText, {} );
	}
	catch (std::string e) {
		exception = e;
	}

	ASSERT_EQ(expectException, exception);
}

TEST(InputParserTests, ParsingWorkflowFile) {
	std::string rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed\n"
		"3 -> 2 -> 2 -> 1 -> 3 -> 2 -> 4";
	testForException(rawWorkflowText, {}, NoException);
	InputMetadata inputMetadata = InputParser::Parse(rawWorkflowText, {} );

	std::vector<std::string> rightVector;
	ASSERT_EQ(3, inputMetadata.NonParsedWorkersMap.size());
	rightVector = { "worker1" };
	ASSERT_EQ(rightVector, inputMetadata.NonParsedWorkersMap[1]);
	rightVector = { "worker2", "arg2_1", "arg2_2" };
	ASSERT_EQ(rightVector, inputMetadata.NonParsedWorkersMap[2]);
	rightVector = { "worker3", "arg3_1" };
	ASSERT_EQ(rightVector, inputMetadata.NonParsedWorkersMap[3]);
	std::vector<int> rightSequence = { 3, 2, 2, 1, 3, 2, 4 };
	ASSERT_EQ(rightSequence, inputMetadata.WorkflowSequence);
}

TEST(InputParserTests, ParsingWorkflowFileWithShortSequence) {
	std::string rawWorkflowText =
		"desc\n"
		"3 = sort\n"
		"csed\n"
		"3";
	testForException(rawWorkflowText, { "-i", "in.txt", "-o", "out.txt" }, NoException);
}

TEST(InputParserTests, ParsingWorkflowFileWithoutSequence) {
	std::string rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowText, {}, NoException);
	InputMetadata inputMetadata = InputParser::Parse(rawWorkflowText, {});

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

TEST(InputParserTests, BeginLabelWithoutWorkersException) {
	std::string rawWorkflowText;
	rawWorkflowText =
		"desc\n"
		"csed";
	testForException(rawWorkflowText, {}, BeginLabelWithoutWorkersException);
}

TEST(InputParserTests, BeginWithoutEndException) {
	std::string rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1";
	testForException(rawWorkflowText, {}, BeginWithoutEndException);
}

TEST(InputParserTests, DuplicatedBeginLabelException) {
	std::string rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"desc\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowText, {}, DuplicatedBeginLabelException);
}

TEST(InputParserTests, DuplicatedIdsException) {
	std::string rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"1 = worker1 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowText, {}, DuplicatedIdsException + ": 1 = worker1 arg2_1 arg2_2");
}

TEST(InputParserTests, EmptyWorkerDefinitionException) {
	std::string rawWorkflowText =
		"desc\n"
		"1 = \n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowText, {}, EmptyWorkerDefinitionException + ": 1 = ");
}

TEST(InputParserTests, NegativeIdException) {
	std::string rawWorkflowText;
	rawWorkflowText =
		"desc\n"
		"-1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowText, {}, NegativeIdException + ": -1 = worker1");
	rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed\n"
		"1 -> -1";
	testForException(rawWorkflowText, {}, NegativeIdException + ": 1 -> -1");
}

TEST(InputParserTests, NoAssingingSymbolException) {
	std::string rawWorkflowText;
	rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"2 =worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowText, {}, NoAssingingSymbolException + ": 2 =worker2 arg2_1 arg2_2");
	rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"2=worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowText, {}, NoAssingingSymbolException + ": 2=worker2 arg2_1 arg2_2");
}

TEST(InputParserTests, UnresolvableLineException) {
	std::string rawWorkflowText;
	rawWorkflowText =
		"desc\n"
		"1 worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowText, {}, UnresolvableLineException + ": 1 worker1");
	rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"meh\n"
		"csed";
	testForException(rawWorkflowText, {}, UnresolvableLineException + ": meh");
}

TEST(InputParserTests, WorkersWithoutBeginLabelException) {
	std::string rawWorkflowText;
	rawWorkflowText =
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowText, {}, WorkersWithoutBeginLabelException);
}

TEST(InputParserTests, WrongIdException) {
	std::string rawWorkflowText;
	rawWorkflowText =
		"desc\n"
		"id1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed";
	testForException(rawWorkflowText, {}, WrongIdException + ": id1 = worker1");
	rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed\n"
		"id1 -> id2";
	testForException(rawWorkflowText, {}, WrongIdException + ": id1 -> id2");
}

TEST(InputParserTests, WrongWorkflowSequenceException) {
	std::string rawWorkflowText =
		"desc\n"
		"1 = worker1\n"
		"2 = worker2 arg2_1 arg2_2\n"
		"3 = worker3 arg3_1\n"
		"csed\n"
		"2 -> 3 ->3";
	testForException(rawWorkflowText, {}, WrongWorkflowSequenceException + ": 2 -> 3 ->3");
}