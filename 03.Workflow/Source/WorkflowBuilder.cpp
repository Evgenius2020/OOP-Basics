#include <map>
#include "WorkflowBuilder.h"
#include "InputWorker.h"
#include "OutputWorker.h"

namespace Building {
	std::vector<Workers::BaseWorker*> WorkflowBuilder::Build(InputMetadata inputMetadata) {
		std::vector<Workers::BaseWorker*> result(0);

		std::map<int, Workers::BaseWorker*> workers;
		Workers::BaseWorker* worker;
		if (inputMetadata.SpecifiedInput != "") {
			worker = &(Workers::InputWorker(-1, { inputMetadata.SpecifiedInput }));
			result.push_back(worker);
		}

		for (int i = 0; i < inputMetadata.WorkflowSequence.size(); ++i) {
		}
		if (inputMetadata.SpecifiedOutput != "") {
			worker = &(Workers::OutputWorker(-1, { inputMetadata.SpecifiedOutput }));
			result.push_back(worker);
		}

		return result;
	}
}
