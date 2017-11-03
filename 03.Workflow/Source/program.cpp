#include <iostream>
#include <string>
#include "WorkflowExecutor.h"
#include "WorkflowBuilder.h"
#include "FileParser.h"

using namespace Workflow;

void main(int argc, char* argv[]) {
	try {
		std::string workflowFileName = argv[1];
		Building::WorkflowBuilder workFlowBuilder(Building::FileParser::Parse(workflowFileName));

		std::string inputWorkerName = "";
		std::string outputWorkerName = "";
		if (argc >= 4) {
			if (argv[2] == "-i") {
				inputWorkerName = argv[3];
			}
			else if (argv[2] == "-o") {
				outputWorkerName = argv[3];
			}
			if (argc == 6) {
				if (argv[4] == "-i") {
					inputWorkerName = argv[5];
				}
				else if (argv[4] == "-o") {
					outputWorkerName = argv[5];
				}
			}
		}
		if (inputWorkerName != "") {
			std::vector<std::string> args = { inputWorkerName };
			workFlowBuilder.AppendInputWorker(Workers::InputWorker(-1, args));
		}
		if (outputWorkerName != "") {
			std::vector<std::string> args = { outputWorkerName };
			workFlowBuilder.AppendOutputWorker(Workers::OutputWorker(-1, args));
		}

		std::vector<Workers::BaseWorker*> workers = workFlowBuilder.GetWorkflow();
		Execution::WorkflowExecutor::Execute(workers);
	}
	catch (std::string exception) {
		std::cerr << exception << std::endl;
	}
}