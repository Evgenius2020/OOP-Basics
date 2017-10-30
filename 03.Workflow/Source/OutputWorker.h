#pragma once
#include "Worker.h"

namespace WorkFlow {
	class OutputWorker : public Worker {
	public:
		OutputWorker(std::vector<std::string> args);

		unsigned int getValidArgsNumber() override;
		std::string execute(std::string input) override;
	};
}