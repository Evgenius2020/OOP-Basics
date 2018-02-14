#pragma once
#include "BaseWorker.h"

namespace Workers {
	class SortWorker : public BaseWorker {
	public: 
		SortWorker(int id, std::vector<std::string> args);

		unsigned int GetValidArgsNumber() override;
		std::vector<std::string> Execute(std::vector<std::string> lines) override;
	};
}