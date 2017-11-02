#pragma once
#include "BaseWorker.h"

namespace Workflow::Workers {
	class OutputWorker : public BaseWorker {
	public:
		OutputWorker(std::vector<std::string> args);

		unsigned int getValidArgsNumber() override;
		std::string execute(std::string input) override;
	};
}