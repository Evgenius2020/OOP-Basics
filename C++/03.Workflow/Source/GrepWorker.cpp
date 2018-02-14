#include "GrepWorker.h"

namespace Workers {
	GrepWorker::GrepWorker(int id, std::vector<std::string> args) : BaseWorker(id, args) {}

	std::vector<std::string> GrepWorker::Execute(std::vector<std::string> lines) {
		std::vector<std::string> result(0);

		for each(std::string str in lines) {
			if (str.find(_args[0]) != std::string::npos) {
				result.push_back(str);
			}
		}

		return result;
	}
}