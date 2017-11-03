#pragma once

#include <vector>
#include <string>
#include "BaseWorker.h"
#include "InputMetadata.h"

namespace Workflow::Building {
	class WorkflowBuilder {
	public:
		static std::vector<Workers::BaseWorker*> Build(InputMetadata inputMetadata);
	};
}