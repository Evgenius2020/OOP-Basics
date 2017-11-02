#include <vector>
#include <string>
#include "WorkflowExecutor.h"
#include "InputWorker.h"
#include "OutputWorker.h"

using namespace Workflow;

void main() {
	std::vector<Workers::BaseWorker*> _workers(0);

	std::vector<std::string> inputWorkerArgs(0);
	inputWorkerArgs.push_back("in.txt");
	Workers::InputWorker inputWorker(inputWorkerArgs);

	std::vector<std::string> outputWorkerArgs(0);
	outputWorkerArgs.push_back("out.txt");
	Workers::OutputWorker outputWorker(outputWorkerArgs);

	_workers.push_back(&inputWorker);
	_workers.push_back(&outputWorker);

	Execution::WorkflowExecutor::Execute(_workers);
}