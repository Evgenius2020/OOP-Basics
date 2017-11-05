#include "BaseWorker.h"

namespace Workers {
	BaseWorker::BaseWorker() : _args(std::vector<std::string>()) {}

	BaseWorker::BaseWorker(const BaseWorker& worker) : _args(std::vector<std::string>(worker._args)) {}

	BaseWorker::BaseWorker(int id, std::vector<std::string> args) : _id(id), _args(args) { };

	int BaseWorker::GetId() {
		return _id;
	}

	std::vector<std::string> BaseWorker::GetArgs() {
		return _args;
	}

	unsigned int BaseWorker::GetValidArgsNumber() {
		return 0;
	}

	std::string BaseWorker::Execute(std::string input) {
		return std::string();
	}
}