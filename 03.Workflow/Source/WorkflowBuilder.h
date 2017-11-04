#pragma once

#include <vector>
#include <string>
#include "BaseWorker.h"
#include "InputMetadata.h"

namespace Building {
	class WorkflowBuilder {
	public:
		static std::vector<Workers::BaseWorker*> Build(InputMetadata inputMetadata);
	};
}