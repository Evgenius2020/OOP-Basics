#pragma once
#include <vector>
#include "BaseWorker.h"

namespace Workflow::Execution {
	class WorkflowExecutor {
	public:
		static void Execute(std::vector<Workers::BaseWorker*> workflow);
	};
}