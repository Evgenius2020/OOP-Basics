#include <string>
#include "StringHelper.h"
#include "InputMetadata.h"
#include "InputParser.h"
#include "WorkflowBuilder.h"
#include "WorkflowExecutor.h"

#include "gtest.cpp"

int main(int argc, char* argv[]) {
#ifdef TESTING
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
#else
	std::vector<std::string> args(0);
	for (int i = 2; i < argc; i++) {
		args.push_back(argv[i]);
	}

	try {
		std::string rawWorkflowText = Tools::StringHelper::GetTextFromFile(argv[1]);
		Building::InputMetadata inputMetadata = Building::InputParser::Parse(rawWorkflowText, args);
		std::vector<Workers::BaseWorker*> workflow = Building::WorkflowBuilder::Build(inputMetadata);
		Execution::WorkflowExecutor::Execute(workflow);
	}
	catch (std::string exception) {
		std::cerr << exception << std::endl;
	}
	return 0;
#endif
}