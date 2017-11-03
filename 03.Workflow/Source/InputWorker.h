#pragma once
#include "BaseWorker.h"

namespace Workflow::Workers {
	class InputWorker : public BaseWorker {
	public:
		InputWorker(int id, std::vector<std::string> args);

		unsigned int GetValidArgsNumber() override;
		std::string Execute(std::string input) override;
	};
}