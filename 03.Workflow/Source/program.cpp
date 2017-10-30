#include <vector>
#include <string>
#include "InputWorker.h"
#include "OutputWorker.h"
#include "program.h"

using namespace WorkFlow;

void main() {
	std::vector<Worker*> workflow(0);

	std::vector<std::string> inputWorkerArgs(0);
	inputWorkerArgs.push_back("in.txt");
	InputWorker inputWorker(inputWorkerArgs);

	std::vector<std::string> outputWorkerArgs(0);
	outputWorkerArgs.push_back("out.txt");
	OutputWorker outputWorker(outputWorkerArgs);

	workflow.push_back(&inputWorker);
	workflow.push_back(&outputWorker);

	std::string buffer = "";
	Worker* current;
	for (unsigned int i = 0; i < workflow.size(); ++i) {
		current = workflow[i];
		buffer = current->execute(buffer);
	}
}