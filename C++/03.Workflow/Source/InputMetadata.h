#pragma once

#include <map>
#include <vector>
#include <string>

namespace Building {
	struct InputMetadata {
		std::string SpecifiedInput;
		std::string SpecifiedOutput;
		std::map<int, std::vector<std::string>> NonParsedWorkersMap;
		std::vector<int> WorkflowSequence;
	};
}