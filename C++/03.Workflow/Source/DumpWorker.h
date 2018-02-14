#pragma once
#include "BaseWorker.h"

namespace Workers {
	class DumpWorker : public BaseWorker {
	public:
		DumpWorker(int id, std::vector<std::string> args);

		std::vector<std::string> Execute(std::vector<std::string> lines) override;
	};
}