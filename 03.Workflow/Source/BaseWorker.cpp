#include "BaseWorker.h"

namespace Workflow::Workers {
	BaseWorker::BaseWorker() : _args(std::vector<std::string>(0)) {}

	BaseWorker::BaseWorker(const BaseWorker& worker) : _args(worker._args) {}

	BaseWorker::BaseWorker(std::vector<std::string> args) : _args(args) { };

	std::vector<std::string> BaseWorker::getArgs() {
		return _args;
	}

	unsigned int BaseWorker::getValidArgsNumber() {
		return 0;
	}

	std::string BaseWorker::execute(std::string input) {
		return std::string();
	}
}