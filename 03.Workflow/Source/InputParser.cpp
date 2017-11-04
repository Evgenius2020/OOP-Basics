#include "InputParser.h"

namespace Building {
	InputMetadata InputParser::Parse(std::vector<std::string> args) {
		InputMetadata result;
		std::string input = "";
		std::string output = "";
		if (args.size() >= 3) {
			if (args[1] == "-i") {
				result.SpecifiedInput = args[2];
			}
			else if (args[1] == "-o") {
				result.SpecifiedOutput = args[2];
			}
			if (args.size() >= 5) {
				if (args[3] == "-i") {
					result.SpecifiedInput = args[4];
				}
				else if (args[3] == "-o") {
					result.SpecifiedOutput = args[4];
				}
			}
		}
		return result;
	}
}
