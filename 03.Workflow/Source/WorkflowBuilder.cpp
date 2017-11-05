#include <map>
#include <sstream>
#include "WorkflowBuilder.h"
#include "InputWorker.h"
#include "OutputWorker.h"
#include "BuildingExceptions.h"

std::string intToStr(int value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

namespace Building {
	std::vector<Workers::BaseWorker*> WorkflowBuilder::Build(InputMetadata inputMetadata) {
		std::vector<Workers::BaseWorker*> result(0);
		std::map<int, Workers::BaseWorker*> workers;
		Workers::BaseWorker* worker;
		for (std::pair<int, std::vector<std::string>> nonParsedWorker : inputMetadata.NonParsedWorkersMap) {
			int workerId = nonParsedWorker.first;
			std::string workerName = nonParsedWorker.second[0];
			std::vector<std::string> workerArgs;
			for (int i = 1; i < nonParsedWorker.second.size(); ++i) {
				workerArgs[i - 1] = nonParsedWorker.second[i];
			}

			if (workerName == "readfile") {
				Workers::InputWorker iworker(-1, { inputMetadata.SpecifiedOutput });
				worker = &iworker;
			}
			else if (workerName == "writefile") {
				Workers::OutputWorker oworker(-1, { inputMetadata.SpecifiedOutput });
				worker = &oworker;
			}
			else {
				throw UnknownWorkerNameException + ": '" + workerName + "'";
			}

			if (worker->GetValidArgsNumber() != workerArgs.size()) {
				throw WrongNumberOfArgs + " (Worker#" + intToStr(workerId) + ")";
			}

			workers[workerId] = worker;
		}

		if (inputMetadata.SpecifiedInput != "") {
			Workers::InputWorker iworker(-1, { inputMetadata.SpecifiedOutput });
			worker = &iworker;
			result.push_back(worker);
		}

		for (int i = 0; i < inputMetadata.WorkflowSequence.size(); ++i) {
			int workerId = inputMetadata.WorkflowSequence[i];
			if (workers.find(workerId) == workers.end()) {
				throw WrongIdInSequenceException + " (Worker#" + intToStr(workerId) + ")";
			}

			if (result.size() == 0) {
				if (typeid(*workers[workerId]) != typeid(Workers::InputWorker)) {
					throw WorkerWithoutInputException + " (Worker#" + intToStr(workerId) + ")";
				}
			}
			else {
				if (typeid(*workers[workerId]) == typeid(Workers::InputWorker)) {
					throw InputWorkerIsNotFirstException;
				}
				if (typeid(*result[result.size() - 1]) == typeid(Workers::OutputWorker)) {
					throw OutputWorkerIsNotLastException;
				}
			}

			result.push_back(workers[workerId]);
		}

		if (inputMetadata.SpecifiedOutput != "") {
			Workers::OutputWorker oworker(-1, { inputMetadata.SpecifiedOutput });
			worker = &oworker;
			result.push_back(worker);
		}

		if (result.size() == 0) {
			throw EmptyWorkflowException;
		}

		if (typeid(*result[result.size() - 1]) == typeid(Workers::OutputWorker)) {
			throw OutputWorkerIsNotLastException;
		}

		return result;
	}
}