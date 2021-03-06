#include "WorkflowExecutor.h"

namespace Execution {
	void WorkflowExecutor::Execute(std::vector<Workers::BaseWorker*> workers) {
		Workers::BaseWorker* currentWorker;
		std::vector<std::string> currentInput;
		for (unsigned int i = 0; i < workers.size(); ++i) {
			currentWorker = workers[i];
			try {
				currentInput = currentWorker->Execute(currentInput);
			}
			catch (std::string e) {
				throw e;
			}
		}
	}
}