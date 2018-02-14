#include <algorithm>
#include "SortWorker.h"

namespace Workers {
	SortWorker::SortWorker(int id, std::vector<std::string> args) : BaseWorker(id ,args) {}

	unsigned int SortWorker::GetValidArgsNumber() {
		return 0;
	}

	std::vector<std::string> SortWorker::Execute(std::vector<std::string> lines) {
		std::vector<std::string> result = lines;
		std::sort(result.begin(), result.end());

		return result;
	}
}
