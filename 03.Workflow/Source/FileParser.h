#pragma once

#include <string>
#include "FileMetadata.h"

namespace Workflow::Building {
	class FileParser {
	public:
		static FileMetadata Parse(std::string filename);
	};
}