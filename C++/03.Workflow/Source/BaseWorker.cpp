#include "BaseWorker.h"

namespace Workers {
	BaseWorker::BaseWorker() : _args((0)) {}

	BaseWorker::BaseWorker(int id, std::vector<std::string> args) : _id(id), _args(args) { };

	int BaseWorker::GetId() {
		return _id;
	}

	std::vector<std::string> BaseWorker::GetArgs() {
		return _args;
	}

	unsigned int BaseWorker::GetValidArgsNumber() {
		return 1;
	}

	std::vector<std::string> BaseWorker::Execute(std::vector<std::string> lines) {
		return lines;
	}

	BaseWorker::~BaseWorker() {
	}
}