#include <map>
#include "WorkflowBuilder.h"

#include "StringHelper.h"
#include "Exceptions.h"

#include "DumpWorker.h"
#include "GrepWorker.h"
#include "ReadfileWorker.h"
#include "ReplaceWorker.h"
#include "SortWorker.h"
#include "WritefileWorker.h"


namespace Building {
	std::vector<Workers::BaseWorker*> WorkflowBuilder::Build(InputMetadata inputMetadata) {
		std::vector<Workers::BaseWorker*> result(0);
		Workers::BaseWorker* worker;

		if (inputMetadata.SpecifiedInput != "") {
			worker = new Workers::ReadfileWorker(-1, { inputMetadata.SpecifiedInput });
			result.push_back(worker);
		}

		for each(int workerId in inputMetadata.WorkflowSequence) {
			if (inputMetadata.NonParsedWorkersMap.find(workerId) == inputMetadata.NonParsedWorkersMap.end()) {
				throw UnknownWorkerIdException + ": Worker#" + Tools::StringHelper::IntToStr(workerId);
			}
			std::vector<std::string> workerInfo = inputMetadata.NonParsedWorkersMap[workerId];
			std::string workerName = workerInfo[0];
			std::vector<std::string> workerArgs(workerInfo.begin() + 1, workerInfo.end());

			if (workerName == "dump") {
				worker = new Workers::DumpWorker(workerId, workerArgs);
			}
			else if (workerName == "grep") {
				worker = new Workers::GrepWorker(workerId, workerArgs);
			}
			else if (workerName == "readfile") {
				worker = new Workers::ReadfileWorker(workerId, workerArgs);
			}
			else if (workerName == "replace") {
				worker = new Workers::ReplaceWorker(workerId, workerArgs);
			}
			else if (workerName == "sort") {
				worker = new Workers::SortWorker(workerId, workerArgs);
			}
			else if (workerName == "writefile") {
				worker = new Workers::WritefileWorker(workerId, workerArgs);
			}
			else {
				throw UnknownWorkerNameException + ": '" + workerName + "'";
			}

			if (worker->GetValidArgsNumber() != workerArgs.size()) {
				throw WrongNumberOfArgsException + ": Worker#" + Tools::StringHelper::IntToStr(workerId);
			}
			result.push_back(worker);
		}

		if (inputMetadata.SpecifiedOutput != "") {
			worker = new Workers::WritefileWorker(-1, { inputMetadata.SpecifiedOutput });
			result.push_back(worker);
		}


		if (result.size() == 0) {
			throw EmptyWorkflowException;
		}
		if (typeid(*result[0]) != typeid(Workers::ReadfileWorker)) {
			throw ReadfileWorkerIsNotFirstException;
		}
		if (typeid(*result[result.size() - 1]) != typeid(Workers::WritefileWorker)) {
			throw WritefileWorkerIsNotLastException;
		}
		for (unsigned int i = 1; i < result.size() - 1; ++i) {
			if (typeid(*result[i]) == typeid(Workers::ReadfileWorker)) {
				throw ReadfileWorkerIsNotFirstException;

			}
			if (typeid(*result[i]) == typeid(Workers::WritefileWorker)) {
				throw WritefileWorkerIsNotLastException;
			}
		}

		return result;
	}
}
