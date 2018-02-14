#pragma once
#include "BaseWorker.h"

namespace Workers {
	class ReadfileWorker : public BaseWorker {
	public:
		ReadfileWorker(int id, std::vector<std::string> args);

		std::vector<std::string> Execute(std::vector<std::string> lines) override;
	};
}