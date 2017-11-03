#pragma once

#include <map>
#include <vector>
#include <string>

namespace Workflow::Building {
	struct FileMetadata {
		bool HaveBegin;
		bool HaveEnd;
		bool HaveDuplicatedId; // More then one workers for id
		std::map<int, std::vector<std::string>> NonParsedWorkersMap; 
		std::vector<int> ExecutionOrder;
	};
}