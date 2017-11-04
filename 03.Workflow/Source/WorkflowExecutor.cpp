#include "WorkflowExecutor.h"

namespace Execution {
	void WorkflowExecutor::Execute(std::vector<Workers::BaseWorker*> workers) {
		std::string buffer = "";
		Workers::BaseWorker* current;
		for (unsigned int i = 0; i < workers.size(); ++i) {
			current = workers[i];
			buffer = current->Execute(buffer);
		}
	}
}