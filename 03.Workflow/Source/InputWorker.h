#pragma once
#include "BaseWorker.h"

namespace Workflow::Workers {
	class InputWorker : public BaseWorker {
	public:
		InputWorker(std::vector<std::string> args);

		unsigned int getValidArgsNumber() override;
		std::string execute(std::string input) override;
	};
}