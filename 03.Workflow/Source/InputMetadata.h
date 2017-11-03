#pragma once

#include <map>
#include <vector>
#include <string>

namespace Workflow::Building {
	struct InputMetadata {
		std::string AdditionalInput;
		std::string AdditionalOutput;
		std::map<int, std::vector<std::string>> NonParsedWorkersMap;
		std::vector<int> ExecutionOrder;
	};
}