#pragma once
#include "BaseWorker.h"

namespace Workers {
	class ReplaceWorker : public BaseWorker {
	public :
		ReplaceWorker(int id, std::vector<std::string> args);

		unsigned int GetValidArgsNumber() override;
		std::vector<std::string> Execute(std::vector<std::string> lines) override;
	};
}