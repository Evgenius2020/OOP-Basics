#pragma once

#include <vector>
#include <string>
#include "BaseWorker.h"
#include "InputWorker.h"
#include "OutputWorker.h"
#include "FileMetadata.h"

namespace Workflow::Building {
	class WorkflowBuilder {
	private:
		std::vector<Workers::BaseWorker*> _workflow;
	public:
		WorkflowBuilder(FileMetadata fileMetadata);

		std::vector<Workers::BaseWorker*> GetWorkflow();

		void AppendInputWorker(Workers::InputWorker inputWorker);
		void AppendOutputWorker(Workers::OutputWorker outputWorker);
		bool ValidateWorkflow();
	};
}