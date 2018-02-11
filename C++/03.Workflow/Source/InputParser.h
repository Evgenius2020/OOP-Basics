#pragma once

#include <string>
#include "InputMetadata.h"

namespace Building {
	class InputParser {
	public:
		static InputMetadata Parse(std::vector<std::string> args);
	};
}