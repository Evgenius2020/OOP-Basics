#include <iostream>
#include <string>
#include "WorkflowExecutor.h"
#include "WorkflowBuilder.h"
#include "InputMetadata.h"
#include "InputParser.h"

using namespace Workflow;

void main(int argc, char* argv[]) {
	std::vector<std::string> args(0);
	for (int i = 1; i < argc; i++) {
		args.push_back(argv[1]);
	}

	try {
		Building::InputMetadata inputMetadata = Building::InputParser::Parse(args);
		std::vector<Workers::BaseWorker*> workflow = Building::WorkflowBuilder::Build(inputMetadata);
		Execution::WorkflowExecutor::Execute(workflow);
	}
	catch (std::string exception) {
		std::cerr << exception << std::endl;
	}
}