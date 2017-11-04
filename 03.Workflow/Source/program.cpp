#include <iostream>
#include <string>
#include "WorkflowExecutor.h"
#include "WorkflowBuilder.h"
#include "InputMetadata.h"
#include "InputParser.h"
#include "gtest.cpp"

int main(int argc, char* argv[]) {
#ifdef TESTING
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
#else
	std::vector<std::string> args(0);
	for (int i = 1; i < argc; i++) {
		args.push_back(argv[1]);
	}

	try {
		std::fstream fs;
		fs.open(args[0], std::fstream::in);
		std::string rawWorkflow((std::istreambuf_iterator<char>()), std::istreambuf_iterator<char>());
		args[0] = rawWorkflow;
		Building::InputMetadata inputMetadata = Building::InputParser::Parse(args);
		std::vector<Workers::BaseWorker*> workflow = Building::WorkflowBuilder::Build(inputMetadata);
		Execution::WorkflowExecutor::Execute(workflow);
	}
	catch (std::string exception) {
		std::cerr << exception << std::endl;
	}
	return 0;
#endif
}