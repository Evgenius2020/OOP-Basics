#pragma once
#include "BaseWorker.h"

namespace Workers {
	class InputWorker : public BaseWorker {
	public:
		InputWorker(int id, std::vector<std::string> args);

		std::vector<std::string> Execute(std::vector<std::string> input) override;
	};
}