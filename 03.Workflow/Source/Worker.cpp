#include "Worker.h"

namespace WorkFlow {
	Worker::Worker() : _args(std::vector<std::string>(0)) {}

	Worker::Worker(const Worker& worker) : _args(worker._args) {}

	Worker::Worker(std::vector<std::string> args) : _args(args) { };

	std::vector<std::string> Worker::getArgs() {
		return _args;
	}

	unsigned int Worker::getValidArgsNumber() {
		return 0;
	}

	std::string Worker::execute(std::string input) {
		return std::string();
	}
}