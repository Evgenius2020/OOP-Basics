#include "gtest.h"
#include "WorkflowExecutor.h"
#include "StringHelper.h"
#include "Exceptions.h"

#include "BaseWorker.h"
#include "DumpWorker.h"
#include "GrepWorker.h"
#include "ReadfileWorker.h"
#include "ReplaceWorker.h"
#include "SortWorker.h"
#include "WritefileWorker.h"

void testWorkflow(std::vector<Workers::BaseWorker*> workflow, std::string input, std::string expectOutput) {
	std::string output;
	Tools::StringHelper::PrintTextToFile("input.txt", input);
	std::string exception = NoException;
	try {
		Execution::WorkflowExecutor::Execute(workflow);
		output = Tools::StringHelper::GetTextFromFile("output.txt");
	}
	catch (std::string e) {
		exception = e;
	}
	ASSERT_EQ(NoException, exception);
	ASSERT_EQ(expectOutput, output);
}

TEST(WorkflowExecutorTests, ReadfileWritefile) {
	std::string input =
		"aaa\n"
		"bbb\n"
		"ccc";
	std::string expectOutput = 
		"aaa\n"
		"bbb\n"
		"ccc";
	std::vector<Workers::BaseWorker*> workflow = {
		new Workers::ReadfileWorker(1, {"input.txt"}),
		new Workers::WritefileWorker(2, {"output.txt"})
	};
	testWorkflow(workflow, input, expectOutput);
}


TEST(WorkflowExecutorTests, AllWorkers) {
	std::string input =
		"ccc\n"
		"aaa\n"
		"bbb\n"
		"cccaaa\n"
		"cccaa";
	std::string expectOutput =
		"\n"
		"aa\n"
		"aaa";
	std::vector<Workers::BaseWorker*> workflow = {
		new Workers::ReadfileWorker(1,{ "input.txt" }),
		new Workers::SortWorker(2, {}),
		new Workers::GrepWorker(4, {"ccc"}),
		new Workers::DumpWorker(6, {"dump.txt"}),
		new Workers::ReplaceWorker(5, {"ccc", ""}),
		new Workers::WritefileWorker(3,{ "output.txt" })
	};
	testWorkflow(workflow, input, expectOutput);
	std::string expectDumpText =
		"ccc\n"
		"cccaa\n"
		"cccaaa";
	ASSERT_EQ(expectDumpText, Tools::StringHelper::GetTextFromFile("dump.txt"));
}