#pragma once
#include "Worker.h"

namespace WorkFlow {
	class InputWorker : public Worker {
	public:
		InputWorker(std::vector<std::string> args);

		unsigned int getValidArgsNumber() override;
		std::string execute(std::string input) override;
	};
}