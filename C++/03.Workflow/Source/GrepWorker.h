#pragma once

#include "BaseWorker.h"

namespace Workers {
	class GrepWorker : public BaseWorker {
	public:
		GrepWorker(int id, std::vector<std::string> args);

		std::vector<std::string> Execute(std::vector<std::string> input) override;
	};
}