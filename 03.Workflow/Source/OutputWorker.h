#pragma once
#include "BaseWorker.h"

namespace Workers {
	class OutputWorker : public BaseWorker {
	public:
		OutputWorker(int id, std::vector<std::string>* args);

		unsigned int GetValidArgsNumber() override;
		std::string Execute(std::string input) override;
	};
}