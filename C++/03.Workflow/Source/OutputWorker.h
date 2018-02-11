#pragma once
#include "BaseWorker.h"

namespace Workers {
	class OutputWorker : public BaseWorker {
	public:
		OutputWorker(int id, std::vector<std::string> args);

		std::vector<std::string> Execute(std::vector<std::string> input) override;
	};
}