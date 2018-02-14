#pragma once
#include "BaseWorker.h"

namespace Workers {
	class WritefileWorker : public BaseWorker {
	public:
		WritefileWorker(int id, std::vector<std::string> args);

		std::vector<std::string> Execute(std::vector<std::string> lines) override;
	};
}