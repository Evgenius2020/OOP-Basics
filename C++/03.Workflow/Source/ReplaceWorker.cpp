#include "ReplaceWorker.h"

namespace Workers {
	ReplaceWorker::ReplaceWorker(int id, std::vector<std::string> args) : BaseWorker(id, args) {}

	unsigned int ReplaceWorker::GetValidArgsNumber() {
		return 2;
	}

	std::vector<std::string> ReplaceWorker::Execute(std::vector<std::string> lines) {
		std::vector<std::string> result(0);
		size_t len = _args[0].length();

		for each (std::string line in lines) {
			int pos;
			while (0 <= (pos = line.find(_args[0]))) {
				line.replace(pos, len, _args[1]);
			}
			result.push_back(line);
		}

		return result;
	}
}